//
// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
//

#import <Foundation/Foundation.h>
#import <AmazonIVSBroadcast/IVSBase.h>
#import <AmazonIVSBroadcast/IVSParticipantInfo.h>

@class IVSStageStream;

NS_ASSUME_NONNULL_BEGIN

IVS_EXPORT
API_AVAILABLE(ios(14))
/// A protocol to implement that can be used to build user interfaces.
/// Implementing a `IVSStageRenderer` provides all the necessary information about a Stage to create a complete UI.
@protocol IVSStageRenderer <NSObject>

/// The connection state of the associated `IVSStage` has changed.
/// @param stage The `IVSStage` that had the connection state change.
/// @param connectionState The new connection state of the Stage.
/// @param error An error, if the state unexpected turned to disconnected.
- (void)stage:(IVSStage *)stage didChangeConnectionState:(IVSStageConnectionState)connectionState withError:(nullable NSError *)error;

/// A new participant has joined the Stage and started publishing.
/// @param stage The `IVSStage` that the participant joined and started publishing.
/// @param participant A description of the participant that joined and started publishing.
- (void)stage:(IVSStage *)stage participantDidJoin:(IVSParticipantInfo *)participant;

/// A participant has left the Stage or stopped publishing.
/// @param stage The `IVSStage` that the participant left or stopped publishing.
/// @param participant A description of the participant that left or stopped publishing.
- (void)stage:(IVSStage *)stage participantDidLeave:(IVSParticipantInfo *)participant;

/// The publish state of a participant has changed.
/// @param stage The `IVSStage` associated with the participant that changed their publish state.
/// @param participant The participant that changed their publish state.
/// @param publishState The new publish state.
- (void)stage:(IVSStage *)stage
  participant:(IVSParticipantInfo *)participant
didChangePublishState:(IVSParticipantPublishState)publishState;

/// The subscribe state of a participant has changed.
/// @param stage The `IVSStage` associated with the participant that changed their subscribe state.
/// @param participant The participant that changed their publish state.
/// @param subscribeState The new subscribe state.
- (void)stage:(IVSStage *)stage
  participant:(IVSParticipantInfo *)participant
didChangeSubscribeState:(IVSParticipantSubscribeState)subscribeState;

/// A participant added media streams that can be rendered locally or attached to an `IVSBroadcastSession`.
/// @param stage The `IVSStage` associated with the new media streams.
/// @param participant The participant associated with the new media streams.
/// @param streams The new media streams.
- (void)stage:(IVSStage *)stage participant:(IVSParticipantInfo *)participant didAddStreams:(NSArray<IVSStageStream *> *)streams;

/// A participant removed media streams. They could have unpublished or stopped sharing a certain media type.
/// @param stage The `IVSStage` associated with the removed media streams.
/// @param participant The participant associated with the removed media streams.
/// @param streams The removed media streams.
- (void)stage:(IVSStage *)stage participant:(IVSParticipantInfo *)participant didRemoveStreams:(NSArray<IVSStageStream *> *)streams;

/// Some media streams have had their muted status changed.
/// @param stage The `IVSStage` associated with the updated media streams.
/// @param participant The participant associated with the updated media streams.
/// @param streams The media streams that have had their mute status changed.
- (void)stage:(IVSStage *)stage participant:(IVSParticipantInfo *)participant didChangeMutedStreams:(NSArray<IVSStageStream *> *)streams;

@end

NS_ASSUME_NONNULL_END
