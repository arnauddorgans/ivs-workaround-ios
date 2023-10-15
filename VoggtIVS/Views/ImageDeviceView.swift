//
//  ImageDeviceView.swift
//  VoggtIVS
//
//  Created by Arnaud Dorgans on 14/10/2023.
//

import SwiftUI
import AmazonIVSBroadcast

struct ImageDeviceView: View {
    let imageDevice: IVSImageDevice

    var body: some View {
        Representable(deviceView: self)
            .id(imageDevice.id)
    }
}

extension ImageDeviceView {
    struct Representable: UIViewRepresentable {
        let deviceView: ImageDeviceView

        func makeUIView(context: Context) -> UIView {
            (try? deviceView.imageDevice.previewView(with: .fill)) ?? UIView()
        }

        func updateUIView(_ uiView: UIViewType, context: Context) { }
    }
}
