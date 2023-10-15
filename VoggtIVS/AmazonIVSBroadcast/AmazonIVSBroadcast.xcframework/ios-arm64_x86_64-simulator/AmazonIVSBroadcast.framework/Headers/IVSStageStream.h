//
// Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.
//

#import <Foundation/Foundation.h>
#import <AmazonIVSBroadcast/IVSBase.h>

@class IVSStageStream;
@protocol IVSDevice;

NS_ASSUME_NONNULL_BEGIN

IVS_EXPORT
API_AVAILABLE(ios(14))
/// A delegate that provides information about the associated `IVSStageStream`.
@protocol IVSStageStreamDelegate <NSObject>

/// The mute status of the associated media stream has changed.
/// @param stream The associated media stream.
- (void)streamDidChangeIsMuted:(IVSStageStream *)stream;

/// The requested RTC stats have been produced.
/// @param stream The stream associated with the RTC stats.
/// @param stats The RTC stats.
- (void)stream:(IVSStageStream *)stream didGenerateRTCStats:(NSDictionary<NSString *, NSDictionary<NSString *, NSString *> *> *)stats;

@end

IVS_EXPORT
API_AVAILABLE(ios(14))
/// A media stream that contains a single `IVSDevice` and a single type of media data (audio or video).
@interface IVSStageStream : NSObject

IVS_INIT_UNAVAILABLE

/// A delegate that can provide updates about this stream.
@property (nonatomic, weak) id<IVSStageStreamDelegate> delegate;

/// The device associated with this stream.
@property (nonatomic, strong, readonly) id<IVSDevice> device;

/// The mute state for this stream. This state applies to the Stage itself, not the local rendering. If this is `true`, nobody can render this stream.
@property (nonatomic, readonly) BOOL isMuted;

/// Request Real Time Communication stats from this stream.
/// @param outError On input, a pointer to an error object. If an error occurs, the pointer is an NSError object that describes the error. If you don’t want error information, pass in nil.
- (BOOL)requestRTCStatsWithError:(NSError *__autoreleasing *)outError;

@end

NS_ASSUME_NONNULL_END
