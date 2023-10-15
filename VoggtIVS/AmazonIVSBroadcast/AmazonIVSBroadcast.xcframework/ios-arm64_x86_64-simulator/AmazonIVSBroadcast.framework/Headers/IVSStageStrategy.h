//
// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
//

#import <Foundation/Foundation.h>
#import <AmazonIVSBroadcast/IVSBase.h>

@class IVSLocalStageStream;
@class IVSParticipantInfo;
@class IVSStage;

NS_ASSUME_NONNULL_BEGIN

/// The options for subscription types
typedef NS_ENUM(NSInteger, IVSStageSubscribeType) {
    /// Do not subscribe to a participant.
    IVSStageSubscribeTypeNone = 0,
    /// Subscribe to this participant, but only receive audio.
    IVSStageSubscribeTypeAudioOnly = 1,
    /// Subscribe to this participant, both audio and video.
    IVSStageSubscribeTypeAudioVideo = 2,
};

IVS_EXPORT
API_AVAILABLE(ios(14))
/// The Strategy is the decision engine associated with an `IVSStage`. It is how the Stage asks the host application what actions to take.
/// If the host application wants to change their answer to a question, they can call `[IVSStage refreshStrategy]`.
@protocol IVSStageStrategy

/// Return an array of media streams to publish with the associated participant.
/// If the return value of this function changes, call `[IVSStage refreshStrategy]` to use the new streams.
/// @param stage The `IVSStage` to publish the streams to.
/// @param participant The participant in question.
- (NSArray<IVSLocalStageStream *> *)stage:(IVSStage *)stage streamsToPublishForParticipant:(IVSParticipantInfo *)participant;

/// Return `true` to publish the associated participant, or `false` to not publish them.
/// If the return value of this function changes, call `[IVSStage refreshStrategy]` update the local publishing state
/// This will only be invoked on participants that have the publish capability.
/// @param stage The `IVSStage` associated with the participant.
/// @param participant The participant in question.
- (BOOL)stage:(IVSStage *)stage shouldPublishParticipant:(IVSParticipantInfo *)participant;

/// Return the `IVSStageSubscribeType` corresponding to the type of media streams desired from the associated participant.
/// This will only be invoked on participants that have the subscribe capability.
/// @param stage The `IVSStage` associated with the participant.
/// @param participant The participant in question.
- (IVSStageSubscribeType)stage:(IVSStage *)stage shouldSubscribeToParticipant:(IVSParticipantInfo *)participant;

@end

NS_ASSUME_NONNULL_END
