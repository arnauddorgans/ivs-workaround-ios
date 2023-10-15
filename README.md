# AmazonIVSBroadcast Stages Workarounds

This project provides a basic implementation of the `AmazonIVSBroadcast` SDK with `Stages` that shows all the bugs with have encountered during the iOS integration, how to reproduce them step by step, and all the workarounds we used.

- No Microphone Sound
- Low audio volume
- Wrong Video quality

We hope this project will help the IVS team to fix the bugs.

## 🔌 Installation

- Pull the project
- Edit `RootViewModel.swift`

```swift
#error("Add Tokens")
let users: [User] = []
```

Provide Viewer and Publisher tokens:
```swift
let users: [User] = [
  .init(name: "Viewer", token: "{{VIEWER_TOKEN}}"),
  .init(name: "Publisher", token: "{{Publisher_TOKEN}}")
]
```

## 🐞 Publisher Bugs

### 🎤 No Microphone Sound

No microphone sound is published when the option `isEchoCancellationEnabled` is set to `false`.

The microphone authorization is not even requested.

#### How to reproduce: 
- Join the stage with a publisher token
- Tap on `Connect`
- Tap on `Connect Camera`
- Tap on `Connect Microphone`
- Tap on `Start broadcasting`

❌ No audio is received on the viewer side

#### How to workaround : 
- Select the `Publisher No Microphone Sound` workaround on the first view
- Join the stage with a publisher token
- Tap on `Connect`
- Tap on `Connect Camera`
- Tap on `Connect Microphone`
- Tap on `Start broadcasting`

✅ Audio is received on the viewer side

### 📹 Video quality

The configuration is not applied when the `IVSLocalStageStreamVideoConfiguration` is set **before** broadcasting.

The default configuration is used (15fps, 360x640).

#### How to reproduce: 
- Join the stage with a publisher token
- Tap on `Connect`
- Tap on `Connect Camera`
- Tap on `Connect Microphone`
- Tap on `Start broadcasting`

❌ The video quality is not applied on the viewer side

#### How to workaround : 
- Select the `Publisher Video Quality` workaround on the first view
- Join the stage with a publisher token
- Tap on `Connect`
- Tap on `Connect Camera`
- Tap on `Connect Microphone`
- Tap on `Start broadcasting`

✅ The video quality is applied on the viewer side

#### How to workaround 2: 
- Join the stage with a publisher token
- Tap on `Connect`
- Tap on `Start broadcasting`
- Tap on `Connect Camera`
- Tap on `Connect Microphone`

✅ The video quality is applied for viewers when connecting the camera **after** starting to broadcast

## 🪲 Viewer Bugs

### 🔊 Low audio volume

By default, when using the SDK, the audio volume is very low as a viewer, especially in speaker mode.

#### How to reproduce: 
- Start to broadcast using another device
- Join the stage with a viewer token
- Tap on `Connect`

 ❌ The audio volume is very low in speaker mode

#### How to workaround: 
- Start to broadcast using another device
- Select the `Viewer Audio Level` workaround on the first view
- Join the stage with a viewer token
- Tap on `Connect`

✅ The audio volume is OK 

#### How to workaround 2: 
- Start to broadcast using another device
- Join the stage with a viewer token
- Tap on `Connect`
- Tap on `Connect Microphone`

✅ The audio volume is OK 

### 🕵️‍♂️ Investigations:
When creating an `IVSStage`, it seems that the SDK set the static variable `IVSBroadcastSession.applicationAudioSessionStrategy` to `stages`, even if we are not using an `IVSBroadcastSession` (which is related to Low Latency streams).

With this audio session strategy, the audio level is very low, but when setting `IVSBroadcastSession.applicationAudioSessionStrategy = .playAndRecord` just **after** creating an `IVSStage`, it seems that it fixes the problem.
