//
//  ContentView.swift
//  VoggtIVS
//
//  Created by Arnaud Dorgans on 14/10/2023.
//

import SwiftUI
import AmazonIVSBroadcast

struct ContentView: View {
    @StateObject var viewModel: ViewModel
    
    var body: some View {
        VStack {
            if let cameraDevice = viewModel.previewCameraDevice {
                ImageDeviceView(imageDevice: cameraDevice)
            } else {
                Color.gray
            }
            ForEach(viewModel.remoteImageDevices, id: \.id) { imageDevice in
                ImageDeviceView(imageDevice: imageDevice)
            }
            button(startTitle: "Connect", stopTitle: "Disconnect", isOn: viewModel.connectionState != .disconnected) {
                viewModel.toggleConnect()
            }
            button(startTitle: "Connect camera", stopTitle: "Disconnect camera", isOn: viewModel.connectCamera) {
                viewModel.toggleCamera()
            }
            button(startTitle: "Connect microphone", stopTitle: "Disconnect microphone", isOn: viewModel.connectMicrophone) {
                viewModel.toggleMicrophone()
            }
            button(startTitle: "Start broadcasting", stopTitle: "Stop broadcasting", isOn: viewModel.shouldBroadcast) {
                viewModel.toggleBroadcasting()
            }
        }
        .overlay(
            HStack {
                Text(viewModel.connectionState.title)
                    .foregroundColor(viewModel.connectionState.color)
                Spacer()
                Text(viewModel.publishState.title)
                    .foregroundColor(viewModel.publishState.color)
            },
            alignment: .top
        )
    }

    private func button(startTitle: String, stopTitle: String, isOn: Bool, action: @escaping () -> Void) -> some View {
        Button(isOn ? stopTitle : startTitle) {
            action()
        }
        .foregroundColor(isOn ? .red : nil)
    }
}

private extension IVSStageConnectionState {
    var color: Color {
        switch self {
        case .connected: .green
        case .connecting: .orange
        case .disconnected: .red
        @unknown default: fatalError()
        }
    }

    var title: String {
        switch self {
        case .connected: "Connected"
        case .connecting: "Connecting"
        case .disconnected: "Disconnected"
        @unknown default: fatalError()
        }
    }
}

private extension IVSParticipantPublishState {
    var color: Color {
        switch self {
        case .published: .green
        case .attemptingPublish: .orange
        case .notPublished: .red
        @unknown default: fatalError()
        }
    }

    var title: String {
        switch self {
        case .published: "Published"
        case .attemptingPublish: "AttemptingPublish"
        case .notPublished: "NotPublished"
        @unknown default: fatalError()
        }
    }
}
