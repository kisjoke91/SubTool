//
//  Wrapper.h
//  test
//
//  Created by Szigeti József on 09.01.21.
//

#import <Foundation/Foundation.h>

typedef NS_ENUM(NSUInteger, SRTError) {
    Success,
    Unspecified,
    FailedOpeningFile,
    MissingTimingSeparator,
    InvalidTimingFormat,
    NoSuchFrameID,
    FrameStartsLaterThanEnds,
    FrameStartsEarlierThanPreviousFrameEnds,
    FrameEndsLaterThanNextFrameStarts
};

@interface SRTFrame : NSObject {
@public 
    int frameid;
    long startTime;
    long endTime;
    NSString * content;
}
@end

@interface SubTool : NSObject
- (void) importFileContent: (NSString *) lines;
- (void) shiftGlobalTiming: (long) offset;
- (BOOL) removeFrame: (int) frameID;
- (NSString *) getOutput;
- (SRTFrame *) getFrame: (int) frameID;
- (SRTError) addFrame: (SRTFrame *) frame;
- (SRTError) setFrame: (SRTFrame *) frame;
- (NSArray <SRTFrame *> *) frames;
@end
