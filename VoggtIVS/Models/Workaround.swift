//
//  Workaround.swift
//  VoggtIVS
//
//  Created by Arnaud Dorgans on 15/10/2023.
//

import Foundation

enum Workaround: CaseIterable {
    case fixPublisherNoMicrophoneSound
    case fixPublisherVideoQuality
    case fixViewerAudioLevel

    var name: String {
        switch self {
        case .fixPublisherNoMicrophoneSound:
            "Publisher No Microphone Sound"
        case .fixPublisherVideoQuality:
            "Publisher Video Quality"
        case .fixViewerAudioLevel:
            "Viewer Audio Level"
        }
    }
}
