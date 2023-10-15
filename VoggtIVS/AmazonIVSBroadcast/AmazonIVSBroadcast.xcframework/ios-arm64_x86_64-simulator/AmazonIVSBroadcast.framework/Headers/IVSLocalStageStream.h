//
// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
//

#import <Foundation/Foundation.h>
#import <AmazonIVSBroadcast/IVSBase.h>
#import <AmazonIVSBroadcast/IVSStageStream.h>

@class IVSLocalStageStreamVideoConfiguration;
@protocol IVSDevice;

NS_ASSUME_NONNULL_BEGIN

IVS_EXPORT
API_AVAILABLE(ios(14))
/// A stage stream that is used to publish local `IVSDevice`s.
@interface IVSLocalStageStream : IVSStageStream

IVS_INIT_UNAVAILABLE

/// Creates a `IVSLocalStageStream` with the associated device.
/// @param device The device to initialize the stream with.
- (instancetype)initWithDevice:(id<IVSDevice>)device;

/// Creates a `IVSLocalStageStream` with the associated device and configuration.
/// @param device The device to initialize the stream with.
/// @param configuration The configuration to initialize the stream with.
- (instancetype)initWithDevice:(id<IVSDevice>)device configuration:(nullable IVSLocalStageStreamVideoConfiguration *)configuration;

/// Sets the mute state for this stream on the Stage. Setting this to `true` will either disable your video, or mute your audio on the Stage, depending on the media type associated with this stream.
/// @param muted The new muted state for the stream.
- (void)setMuted:(BOOL)muted;

/// Updates the configuration of this stream.
/// @param configuration The new configuration for the stream.
- (void)setConfiguration:(IVSLocalStageStreamVideoConfiguration *)configuration;

@end

NS_ASSUME_NONNULL_END
