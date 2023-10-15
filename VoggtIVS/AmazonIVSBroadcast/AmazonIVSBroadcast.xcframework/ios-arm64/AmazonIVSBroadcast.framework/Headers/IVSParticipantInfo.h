//
// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
//

#import <Foundation/Foundation.h>
#import <AmazonIVSBroadcast/IVSBase.h>

NS_ASSUME_NONNULL_BEGIN

/// A bitwise enum representing the capabilities that can be performed by this `IVSParticipantInfo`.
typedef NS_OPTIONS(NSUInteger, IVSParticipantCapability) {
    /// No actions can be taken on this participant
    IVSParticipantCapabilityNone = 0,
    /// This participant can be published
    IVSParticipantCapabilityPublish = 1 << 0,
    /// This participant can be subscribed to
    IVSParticipantCapabilitySubscribe = 1 << 1,
};

/// The various potential publish states for a participant
typedef NS_ENUM(NSUInteger, IVSParticipantPublishState) {
    /// The participant is not publishing and not attempting to publish
    IVSParticipantPublishStateNotPublished,
    /// The participant is attempting to publish
    IVSParticipantPublishStateAttemptingPublish,
    /// The participant is publishing
    IVSParticipantPublishStatePublished
};

/// The various potential subscribe states for a participant
typedef NS_ENUM(NSUInteger, IVSParticipantSubscribeState) {
    /// The participant is not being subscribed to
    IVSParticipantSubscribeStateNotSubscribed,
    /// An subscription is being established to the remote participant
    IVSParticipantSubscribeStateAttemptingSubscribe,
    /// There is a connected subscription to the remote participant
    IVSParticipantSubscribeStateSubscribed
};

IVS_EXPORT
API_AVAILABLE(ios(14))
/// Information about a participant. The properties in this class will remain constant throughout its lifetime, with the exception of `userInfo`.
@interface IVSParticipantInfo : NSObject

IVS_INIT_UNAVAILABLE

/// A unique ID assigned to this participant.
@property (nonatomic, strong, readonly) NSString *participantId;
/// Attributes associated with this participant.
@property (nonatomic, strong, readonly) NSDictionary<NSString *, NSString *> *attributes;
/// This represents if the participant is local (associated with the token used on this device  to join the Stage).
@property (nonatomic, readonly) BOOL isLocal;
/// This represents the capabilities that can be performed on this participant.
@property (nonatomic, readonly) IVSParticipantCapability capabilities;
/// This object exists for use by the developer, to store information that might be associated with this participant.
/// This object will never be accessed by the SDK, and changes will not be synced to remote SDK `userInfo` objects.
@property (nonatomic, strong, readonly) NSMutableDictionary<NSString *, id> *userInfo;

@end

NS_ASSUME_NONNULL_END
