import KPU as kpu
import MakerPlayground as mp

class MP_K210_KPU_ObjectDetector:
    def __init__(self, address, modelSize, anchor, threshold, nmsThreshold, numAnchor, outputShape):
        self.address = address
        if modelSize == 0:
            self.modelWidth = 224
            self.modelHeight = 224
        else:
            self.modelWidth = 320
            self.modelHeight = 240
        self.anchor = anchor
        self.threshold = threshold
        self.nmsThreshold = nmsThreshold
        self.numAnchor = numAnchor
        self.outputShape = outputShape

    def init(self):
        self.task = kpu.load(int(self.address)) # kpu.load("/sd/face.kmodel")
        if self.outputShape != '-':
            shape = self.outputShape.split(',')
            kpu.set_outputs(self.task, int(shape[0]), int(shape[1]), int(shape[2]), int(shape[3]))
        kpu.init_yolo2(self.task, self.threshold, self.nmsThreshold, int(self.numAnchor), tuple([float(a) for a in self.anchor.split(',')]))
        self.result = None
        return mp.ERR_OK

    def update(self, currentTime):
        pass

    def printStatus(self):
        pass

    def detect(self, image):
        if self.modelWidth != image.width() or self.modelHeight != image.height():
            image = image.resize(self.modelWidth, self.modelHeight)
            image.pix_to_ai()
        self.width = image.width()
        self.height = image.height()
        self.result = kpu.run_yolo2(self.task, image)

    def containDetection(self, classID, minConfidence, minX, minY, maxX, maxY):
        if not self.result:
            return False

        minX = minX * self.width
        minY = minY * self.height
        maxX = maxX * self.width
        maxY = maxY * self.height
        for r in self.result:
            box_xmin = r.rect()[0]
            box_ymin = r.rect()[1]
            box_xmax = box_xmin + r.rect()[2]
            box_ymax = box_ymin + r.rect()[3]
            if ((r.classid() == classID) and (r.value() >= minConfidence/100.0)
                and ((box_xmin >= minX and box_xmin <= maxX and box_ymin >= minY and box_ymin <= maxY)
                    or (box_xmax >= minX and box_xmax <= maxX and box_ymax >= minY and box_ymax <= maxY))):
                return True

        return False

    def notContainDetection(self, classID, minConfidence, minX, minY, maxX, maxY):
        return not self.containDetection(classID, minConfidence, minX, minY, maxX, maxY)

    def hasDetection(self):
        return self.result

    def noDetection(self):
        return not self.result

    def getClassID(self):
        if self.result and len(self.result) >= 1:
            return self.result[0].classid()
        else:
            return -1

    def getLeft(self):
        if self.result and len(self.result) >= 1:
            return self.result[0].rect()[0] / self.width
        else:
            return 0

    def getTop(self):
        if self.result and len(self.result) >= 1:
            return self.result[0].rect()[1] / self.height
        else:
            return 0

    def getRight(self):
        if self.result and len(self.result) >= 1:
            return (self.result[0].rect()[0] + self.result[0].rect()[2]) / self.width
        else:
            return 0

    def getBottom(self):
        if self.result and len(self.result) >= 1:
            return (self.result[0].rect()[1] + self.result[0].rect()[3]) / self.height
        else:
            return 0
    
    def getObject_Count(self):
        if self.result:
            return len(self.result)
        else:
            return 0