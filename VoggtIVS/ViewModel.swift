//
//  ViewModel.swift
//  VoggtIVS
//
//  Created by Arnaud Dorgans on 14/10/2023.
//

import Foundation
import AmazonIVSBroadcast

@MainActor
final class ViewModel: NSObject, ObservableObject {
    @Published private(set) var connectCamera: Bool = false
    @Published private(set) var connectMicrophone: Bool = false
    @Published private(set) var shouldBroadcast: Bool = false

    @Published private var cameraStream: IVSLocalStageStream?
    @Published private var microphoneStream: IVSLocalStageStream?

    @Published private(set) var connectionState: IVSStageConnectionState = .disconnected
    @Published private(set) var publishState: IVSParticipantPublishState = .notPublished
    @Published private var remoteStreams: [IVSStageStream] = []

    private lazy var deviceDiscovery = IVSDeviceDiscovery()
    private lazy var videoConfiguration: IVSLocalStageStreamVideoConfiguration = {
        let videoConfiguration = IVSLocalStageStreamVideoConfiguration()
        try? videoConfiguration.setTargetFramerate(30)
        try? videoConfiguration.setSize(.init(width: 720, height: 1280))
        try? videoConfiguration.setMaxBitrate(2_500_000)
        videoConfiguration.degradationPreference = .maintainResolution
        videoConfiguration.simulcast.enabled = false
        return videoConfiguration
    }()

    private var stage: IVSStage!
    private let token: String
    private let workarounds: Set<Workaround>

    var previewCameraDevice: IVSImageDevice? {
        cameraStream?.device as? IVSImageDevice
    }

    var remoteImageDevices: [IVSImageDevice] {
        remoteStreams.compactMap { $0.device as? IVSImageDevice }
    }

    init(token: String, workarounds: Set<Workaround>) {
        self.token = token
        self.workarounds = workarounds
        super.init()
        stage = try! IVSStage(token: token, strategy: self)
        stage.addRenderer(self)
        if workarounds.contains(.fixViewerAudioLevel) {
            IVSBroadcastSession.applicationAudioSessionStrategy = .playAndRecord
        }
    }

    func toggleConnect() {
        switch connectionState {
        case .connected, .connecting:
            stage.leave()
        case .disconnected:
            try! stage.join()
        @unknown default:
            fatalError()
        }
    }

    func toggleBroadcasting() {
        shouldBroadcast.toggle()
        stage.refreshStrategy()
    }

    func toggleCamera() {
        connectCamera.toggle()
        updateDevices()
    }

    func toggleMicrophone() {
        connectMicrophone.toggle()
        updateDevices()
    }
}

private extension ViewModel {
    func updateDevices() {
        let devices: [IVSDevice] = {
            guard connectCamera || connectMicrophone else { return [] }
            return deviceDiscovery.listLocalDevices().sorted(by: { lhs, _ in lhs.descriptor().isDefault })
        }()
        createOrUpdateDevice(type: .camera, devices: devices, stream: &cameraStream, enable: connectCamera)
        createOrUpdateDevice(type: .microphone, devices: devices, stream: &microphoneStream, enable: connectMicrophone)
        stage.refreshStrategy()
    }

    func createOrUpdateDevice(type: IVSDeviceType, devices: [IVSDevice], stream: inout IVSLocalStageStream?, enable: Bool) {
        guard enable else {
            stream = nil
            return
        }
        if stream == nil {
            if let device = devices.filter({ $0.descriptor().type == type }).first {
                stream = .init(device: device, configuration: videoConfiguration)
                if let microphone = device as? IVSMicrophone {
                    if workarounds.contains(.fixPublisherNoMicrophoneSound) {
                        microphone.isEchoCancellationEnabled = true // Doesn't work without echo cancellation
                    }
                }
            }
        } else {
            stream?.setConfiguration(videoConfiguration)
        }
        if let stream, let device = stream.device as? IVSMultiSourceDevice {
            let sources = device.listAvailableInputSources()
                .sorted(by: { lhs, _ in lhs.isDefault })
            if let source = sources.first {
                device.setPreferredInputSource(source)
            }
        }
    }
}

// MARK: IVSStageStrategy
extension ViewModel: IVSStageStrategy {
    func stage(_ stage: IVSStage, shouldPublishParticipant participant: IVSParticipantInfo) -> Bool {
        shouldBroadcast
    }

    func stage(_ stage: IVSStage, streamsToPublishForParticipant participant: IVSParticipantInfo) -> [IVSLocalStageStream] {
        let streams = [
            connectCamera ? cameraStream : nil,
            connectMicrophone ? microphoneStream : nil
        ].compactMap { $0 }
        return streams
    }

    func stage(_ stage: IVSStage, shouldSubscribeToParticipant participant: IVSParticipantInfo) -> IVSStageSubscribeType {
        .audioVideo
    }
}

// MARK: IVSStageRenderer
extension ViewModel: IVSStageRenderer {
    func stage(_ stage: IVSStage, didChange connectionState: IVSStageConnectionState, withError error: Error?) {
        self.connectionState = connectionState
    }
    
    func stage(_ stage: IVSStage, participant: IVSParticipantInfo, didChange publishState: IVSParticipantPublishState) {
        guard participant.isLocal else { return }
        self.publishState = publishState
        if workarounds.contains(.fixPublisherVideoQuality) {
            if case .published = publishState {
                updateDevices()
            }
        }
    }

    func stage(_ stage: IVSStage, participant: IVSParticipantInfo, didAdd streams: [IVSStageStream]) {
        guard !participant.isLocal else { return }
        remoteStreams.append(contentsOf: streams)
    }

    func stage(_ stage: IVSStage, participant: IVSParticipantInfo, didRemove streams: [IVSStageStream]) {
        guard !participant.isLocal else { return }
        let ids = streams.map(\.id)
        remoteStreams.removeAll(where: { ids.contains($0.id) })
    }

    func stage(_ stage: IVSStage, participantDidJoin participant: IVSParticipantInfo) { }
    func stage(_ stage: IVSStage, participantDidLeave participant: IVSParticipantInfo) { }
    func stage(_ stage: IVSStage, participant: IVSParticipantInfo, didChangeMutedStreams streams: [IVSStageStream]) { }
    func stage(_ stage: IVSStage, participant: IVSParticipantInfo, didChange subscribeState: IVSParticipantSubscribeState) { }
}

extension IVSStageStream {
    var id: String {
        device.id
    }
}

extension IVSDevice {
    var id: String {
        descriptor().urn
    }
}
