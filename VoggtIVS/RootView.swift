//
//  RootView.swift
//  VoggtIVS
//
//  Created by Arnaud Dorgans on 14/10/2023.
//

import SwiftUI

struct RootView: View {
    @StateObject var viewModel: RootViewModel
    @State var selectedWorkarounds: Set<Workaround> = Set(Workaround.allCases)

    var body: some View {
        NavigationStack {
            List {
                Section("Workarounds") {
                    ForEach(Workaround.allCases, id: \.self) { workaround in
                        HStack {
                            Text(workaround.name)
                            Spacer()
                            if selectedWorkarounds.contains(workaround) {
                                Image(systemName: "checkmark")
                            }
                        }
                        .onTapGesture {
                            if selectedWorkarounds.contains(workaround) {
                                selectedWorkarounds.remove(workaround)
                            } else {
                                selectedWorkarounds.insert(workaround)
                            }
                        }
                    }
                }
                Section("Token") {
                    ForEach(viewModel.users, id: \.token) { user in
                        NavigationLink(user.name) {
                            ContentView(viewModel: .init(token: user.token, workarounds: selectedWorkarounds))
                        }
                    }
                }
            }
        }
    }
}
