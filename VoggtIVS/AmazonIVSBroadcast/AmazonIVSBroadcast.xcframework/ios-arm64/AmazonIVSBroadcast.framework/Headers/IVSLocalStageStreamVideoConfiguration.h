//
// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
//

#import <Foundation/Foundation.h>
#import <CoreGraphics/CoreGraphics.h>
#import <AmazonIVSBroadcast/IVSBase.h>
#import <AmazonIVSBroadcast/IVSBroadcastConfiguration.h>

NS_ASSUME_NONNULL_BEGIN

/// The stage degradation preference.
typedef NS_ENUM(NSInteger, IVSLocalStageStreamVideoConfigurationDegradationPreference) {
    /// Degrade resolution in order to maintain framerate.
    IVSLocalStageStreamVideoConfigurationDegradationPreferenceMaintainFramerate = 1,
    /// Degrade framerate in order to maintain resolution.
    IVSLocalStageStreamVideoConfigurationDegradationPreferenceMaintainResolution,
    /// Degrade a balance of framerate and resolution.
    IVSLocalStageStreamVideoConfigurationDegradationPreferenceBalanced,
} NS_SWIFT_NAME(IVSLocalStageStreamVideoConfiguration.DegradationPreference);

@class IVSMixerConfiguration;

/// A configuration object describing simulcast configuration
IVS_EXPORT
API_AVAILABLE(ios(14))
@interface IVSSimulcastConfiguration : NSObject

/// Whether simulcast is enabled.
///
/// By default this is `YES`.
@property (nonatomic) BOOL enabled;

@end

IVS_EXPORT
API_AVAILABLE(ios(14))
/// A collection of `IVSStageConfiguration` objects.
@interface IVSLocalStageStreamVideoConfiguration : NSObject

/// The maximum bitrate for the publishing video stream.
/// By default this is `900,000`.
@property (nonatomic, readonly) NSInteger maxBitrate;

/// Sets the maximum bitrate for the publishing video stream. This value must be between 100k and 2,500k
/// If the provided bitrate falls outside this range, bitrate will not be set and the provided outError will be set.
/// @param maxBitrate the maximum bitrate for the publishing video stream
/// @param outError On input, a pointer to an error object. If an error occurs, the pointer is an NSError object that describes the error. If you don’t want error information, pass in nil.
/// @return if the set operation is successful or not.
- (BOOL)setMaxBitrate:(NSInteger)maxBitrate error:(NSError* __autoreleasing*)outError;

/// The minimum bitrate for the output video stream.
/// By default this is `100,000`.
@property (nonatomic, readonly) NSInteger minBitrate;

/// Sets the minimum bitrate for the publishing video stream. This value must be between 100k and 2,500k
/// If the provided bitrate falls outside this range, bitrate will not be set and the provided outError will be set.
/// This is ignored when simulcast is enabled.
/// @param minBitrate the minimum bitrate for the publishing video stream
/// @param outError On input, a pointer to an error object. If an error occurs, the pointer is an NSError object that describes the error. If you don’t want error information, pass in nil.
/// @return if the set operation is successful or not.
- (BOOL)setMinBitrate:(NSInteger)minBitrate error:(NSError* __autoreleasing*)outError;

/// The resolution of the output video stream.
/// By default this is `360x640`.
@property (nonatomic, readonly) CGSize size;

/// Sets the resolution of the publishing video stream.
/// The width and height must both be between 160 and 1280, and the maximum total number of pixels
/// is 921,600. So the smallest size you can provide is 160x160, and the largest
/// is either 720x1280 or 1280x720.
/// If the provided resolution does not meet this criteria, the resolution will not be set and the provided outError will be set.
/// @param size The resolution of the publishing video stream
/// @param outError On input, a pointer to an error object. If an error occurs, the pointer is an NSError object that describes the error. If you don’t want error information, pass in nil.
/// @return if the set operation is successful or not.
- (BOOL)setSize:(CGSize)size error:(NSError* __autoreleasing*)outError;

/// The target framerate of the publishing video stream.
/// By default this is `15`.
@property (nonatomic, readonly) NSInteger targetFramerate;

/// Sets the target framerate of the publishing video stream. This must be between 10 and 30
/// If the provided framerate falls outside this range, the framerate will not be set and the provided outError will be set.
/// @param targetFramerate The target framerate for the publishing video stream
/// @param outError On input, a pointer to an error object. If an error occurs, the pointer is an NSError object that describes the error. If you don’t want error information, pass in nil.
/// @return if the set operation is successful or not.
- (BOOL)setTargetFramerate:(NSInteger)targetFramerate error:(NSError* __autoreleasing*)outError;

/// When encoding video, and some constraint (bandwidth, CPU) prevents encoding at the configured framerate and resolution,
/// the encoder must make a choice on how to modify the encoding parameters. This value is used to indicate that choice.
/// This is ignored when simulcast is enabled.
@property (nonatomic) IVSLocalStageStreamVideoConfigurationDegradationPreference degradationPreference;

/// This describes the simulcast configuration for the video stream.
@property (nonatomic, strong) IVSSimulcastConfiguration* simulcast;

@end

NS_ASSUME_NONNULL_END
