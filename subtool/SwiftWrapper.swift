//
//  SwiftWrapper.swift
//  SRTool
//
//  Created by Szigeti József on 10.01.21.
//

import SwiftUI

class ObservedSubTool: SubTool, ObservableObject {
    
    override init() {
        super.init()
    }
    
    override func importFileContent(_ lines: String!) {
        super.importFileContent(lines)
        frames = getFrames()
    }
    
    override func shiftGlobalTiming(_ offset: Int) {
        super.shiftGlobalTiming(offset)
        frames = getFrames()
    }
    
    override func add(_ frame: SRTFrame!) -> SRTError {
        let e = super.add(frame)
        frames = getFrames()
        return e
    }
    
    override func removeFrame(_ frameID: Int32) -> Bool {
        let e = super.removeFrame(frameID)
        frames = getFrames()
        return e
    }
    
    override func setFrame(_ frame: SRTFrame!) -> SRTError {
        
        if frame.frameid == 0 {return .NoSuchFrameID}
        
        let e = super.setFrame(frame)
        frames = getFrames()
        return e
    }
    
    func currentFrame(_ currentTime: Int) -> SRTFrame? {
        
        for i in 0..<frames.count {
            
            let f = frames[i]
            
            if (f.startTime <= currentTime &&
                    f.endTime >= currentTime) {
                return f
            }
        }
        return nil
    }
    
    @Published var frames: [SRTFrame] = [SRTFrame]()
}

