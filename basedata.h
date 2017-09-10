#ifndef BASE_DATA_H
#define BASE_DATA_H

namespace IconStateNS{
    // 任务栏图标状态
    enum IconState_ {
        Normal  = 1,    // 正常状态，进行中，绿色
        Pause   = 2,    // 暂停，黄色
        Stop    = 3,    // 停止，红色
    };

}

namespace BaseData{
    // 同一命名空间内不能重复enum值名称
    // 计时状态
    enum TickState_ {
        Init        = 10,   // 初始状态
        Count       = 12,   // 计时中
        Break       = 19,   // 休息状态
        LongBreak   = 23,   // 长休息状态

        Pause       = 15,   // 暂停
        Stop        = 16,   // 停止
        Overtime    = 25,   // 超时
    };
}

// 通过别名和命名空间，实现使用相等的ENUM名称，如Pause、Stop
// 使用：TickState::Stop、IconState::Stop

//typedef BaseData::IconState_ IconState;
typedef IconStateNS::IconState_ IconState;
typedef BaseData::TickState_ TickState;

#endif // BASE_DATA_H
