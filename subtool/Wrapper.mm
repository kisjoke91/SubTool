//
//  Wrapper.mm
//  test
//
//  Created by Szigeti József on 09.01.21.
//

#import "Wrapper.h"
#import "subtool.h"




@implementation SRTFrame
@end


@implementation SubTool {
    Subtool t;
}

- (void) importFileContent: (NSString *) lines {
    self->t.getMainFileFromString([lines cStringUsingEncoding:NSUTF8StringEncoding]);
}

- (void) shiftGlobalTiming: (long) offset {
    self->t.shiftTimingOfMainFile(offset);
}

- (NSString *) getOutput {
    return [NSString stringWithUTF8String:self->t.getOutput().c_str()];
}

- (SRTFrame *) getFrame: (int) frameID {
    
    SRTFrame * f = [SRTFrame new];
    srt_frame_t n;
    
    n = self->t.getFrameFromMainFile(frameID);
    
    if (n.id == SRT_INVALID_ID) {
        return nil;
    }
    
    f.frameid = n.id;
    f.startTime = n.startTime;
    f.endTime = n.endTime;
    f.content = [NSString stringWithUTF8String:n.content.c_str()];
    
    return f;
}

- (SRTError) addFrame: (SRTFrame *) frame {
    
    srt_frame_t f;
    
    f.id = frame.frameid;
    f.startTime = frame.startTime;
    f.endTime = frame.endTime;
    f.content = [frame.content cStringUsingEncoding:NSUTF8StringEncoding];
    
    return (SRTError) self->t.addFrameToMainFile(f);
}

- (SRTError) setFrame: (SRTFrame *) frame {
    
    srt_frame_t f;
    
    f.id = frame.frameid;
    f.startTime = frame.startTime;
    f.endTime = frame.endTime;
    f.content = [frame.content cStringUsingEncoding:NSUTF8StringEncoding];
    
    return (SRTError) self->t.setFrameInMainFile(f);
}

- (BOOL) removeFrame: (int) frameID {
    return self->t.removeFrameFromMainFile(frameID);
}

- (NSArray <SRTFrame *> *) getFrames {
    
    NSMutableArray * a = [NSMutableArray new];

    int i = 1;
    
    for(auto n: self->t.mainFile) {
        
        SRTFrame * f = [SRTFrame new];
        
        f.frameid = i;
        f.startTime = n.startTime;
        f.endTime = n.endTime;
        f.content = [NSString stringWithUTF8String:n.content.c_str()];
        
        [a addObject: f];
        
        i ++;
    }

    return a;
}

@end
