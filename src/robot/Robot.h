
#ifndef AUBOROBOTQT_ROBOT_H
#define AUBOROBOTQT_ROBOT_H

#include "serviceinterface.h"
#include "AuboRobotMetaType.h"
#include <string.h>
#include <math.h>

const double DE2RA = M_PI / 180.0f;
const double RA2DE = 180.0f / M_PI;

class Robot {
private:
    static Robot *instance;
    //AuBo的对外服务接口
    ServiceInterface robotService;
public:
    Robot();

    ~Robot();

    //获取Robot实例
    static Robot *getInstance();

    class CGarbo {
    public:
        ~CGarbo() {
            if (Robot::instance) {
                delete Robot::instance;
                Robot::instance = nullptr;
            }
        }
    };

    //程序结束时释放Robot内存
    static CGarbo cGarbo;

    //连接
    int connect(char *path, int port);

    //断开连接
    void disConnect();

    /**
     * 获取关节状态
     * @param jointStatus 存放关节状态
     * @param size  关节数量
     * @return 获取成功或者失败  aubo_robot_namespace::InterfaceCallSuccCode为成功
     */
    int robotServiceGetRobotJointStatus(aubo_robot_namespace::JointStatus *jointStatus, int size);

    //设置关节运动的最大加速度
    int robotServiceSetGlobalMoveJointMaxAcc(const aubo_robot_namespace::JointVelcAccParam &moveMaxAcc);

    //设置关节运动的最大速度
    int robotServiceSetGlobalMoveJointMaxVelc(const aubo_robot_namespace::JointVelcAccParam &moveMaxVelc);

    //末端型运动的最大加速度和速度
    int robotServiceSetGlobalMoveEndMaxLineAcc(double moveMaxAcc);

    int robotServiceSetGlobalMoveEndMaxLineVelc(double moveMaxVelc);

    int robotServiceSetGlobalMoveEndMaxAngleAcc(double moveMaxAcc);

    int robotServiceSetGlobalMoveEndMaxAngleVelc(double moveMaxVelc);

    /**
     * 添加路点
     * @param wayPoint
     * @return
     */
    int robotServiceAddGlobalWayPoint(const double jointAngle[aubo_robot_namespace::ARM_DOF]);

    /**
     * 圆轨迹时圆的圈数
     * @param times
     */
    void robotServiceSetGlobalCircularLoopTimes(int times);

    //movej运动
    int moveJ(double jointAngle[aubo_robot_namespace::ARM_DOF], bool IsBolck = true);

    //moveL
    int moveL(aubo_robot_namespace::wayPoint_S &wayPoint, bool IsBolck);

    //第二种moveL
    int moveL(const double poses[aubo_robot_namespace::ARM_DOF], bool IsBolck = true);
    int moveLwithJoint(double jointAngle[aubo_robot_namespace::ARM_DOF], bool IsBolck = true);

    //设置运动属性的偏移
    int robotServiceSetMoveRelativeParam();

    /**
     * rpy转四元素
     * @param rpy
     * @param ori
     * @return
     */
    int RPYToQuaternion(const aubo_robot_namespace::Rpy &rpy, aubo_robot_namespace::Ori &ori);

    /**
     * @brief quaternionToRPY     四元素转欧拉角
     * @param ori　　　　　姿态的四元素表示方法
     * @param rpy　　　　　姿态的欧拉角表示方法
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int quaternionToRPY(const aubo_robot_namespace::Ori &ori, aubo_robot_namespace::Rpy &rpy);


    //获取当前关节角信息
    int robotServiceGetJointAngleInfo(aubo_robot_namespace::JointParam &jointParam);

    /**
     * @brief robotServiceGetCurrentWaypointInfo   获取机械臂当前路点信息
     * @param wayPoint   输出参数
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceGetCurrentWaypointInfo(aubo_robot_namespace::wayPoint_S &wayPoint);
    /**
     * 轨迹运动
     * @param subMoveMode
     * @param IsBolck
     * @return
     */
    int moveTrack(aubo_robot_namespace::move_track subMoveMode, bool IsBolck);

    /**
     * 初始化全局的运动属性
     * @return
     */
    int robotServiceInitGlobalMoveProfile();

    /**
     * 添加路点，一般用于robotServiceTrackMove中
     * @param wayPoint 路点坐标以及姿态
     * @return
     */
    int addGlobalWayPoint(const aubo_robot_namespace::wayPoint_S &wayPoint);

    /**
     * 路点关节角度
     * @param jointAngle
     * @return
     */
    int addGlobalWayPoint(const double jointAngle[aubo_robot_namespace::ARM_DOF]);

    /**
     * 获取路点
     * @param wayPointVector
     */
    void getGlobalWayPointVector(std::vector<aubo_robot_namespace::wayPoint_S> &wayPointVector);

    /**
     * 获取交融半径
     * @return
     */
    float getGlobalBlendRadius();

    /**
     * 设置交融半径
     * @param value
     * @return
     */
    int setGlobalBlendRadius(float value);

    /**
     * 保持当前位姿通过直线运动的方式运动到目标位置
     * @param userCoord
     * @param toolEndPositionOnUserCoord
     * @param toolInEndDesc
     * @param IsBolck
     * @return
     */
    int moveLineToTargetPosition(const aubo_robot_namespace::CoordCalibrateByJointAngleAndTool &userCoord,
                                 const aubo_robot_namespace::Pos &toolEndPositionOnUserCoord,
                                 const aubo_robot_namespace::ToolInEndDesc &toolInEndDesc,     //相对于用户坐标系的目标位置
                                 bool IsBolck = false);                                          //是否阻塞


    /** 保持当前位姿通过关节运动的方式运动到目标位置   参数描述参考robotMoveLineToTargetPosition **/
    int moveJointToTargetPosition(const aubo_robot_namespace::CoordCalibrateByJointAngleAndTool &userCoord,
                                  const aubo_robot_namespace::Pos &toolEndPositionOnUserCoord,
                                  const aubo_robot_namespace::ToolInEndDesc &toolInEndDesc,    //相对于用户坐标系的目标位置
                                  bool IsBolck = false);

    /**
     * @brief robotServiceGetCurrentWaypointInfo   获取机械臂当前路点信息
     * @param wayPoint   输出参数
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int getCurrentWaypointInfo(aubo_robot_namespace::wayPoint_S &wayPoint);

    /**
     * 反解
     * @param startPointJointAngle 当前机械臂的角度
     * @param position 目标位置
     * @param ori 目标姿态(四元数)
     * @param wayPoint 接收反解的结果
     * @return
     */
    int robotServiceRobotIk(const double *startPointJointAngle, const aubo_robot_namespace::Pos &position,
                            const aubo_robot_namespace::Ori &ori, aubo_robot_namespace::wayPoint_S &wayPoint);

    /**
     * @brief 正解　　　　　此函数为正解函数，已知关节角求对应位置的位置和姿态。
     * @param jointAngle  六个关节的关节角  　　　输入参数   单位:弧度(rad)
     * @param size        关节角数组长度   规定为6个
     * @param wayPoint    正解结果    　　　输出参数
     * 　　　结果示例: 六个关节角 {'joint': [1.0, 1.0, 1.0, 1.0, 1.0, 1.0],
     *              位置 'pos': [-0.06403157614989634, -0.4185973810159096, 0.816883228463401],
     *              姿态 'ori': [-0.11863209307193756, 0.3820514380931854, 0.0, 0.9164950251579285]}
     *
     * @return　调用成功返回ErrnoSucc;错误返回错误号  调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceRobotFk(const double *jointAngle, int size, aubo_robot_namespace::wayPoint_S &wayPoint);

    /**
     * @brief robotServiceRegisterRealTimeJointStatusCallback   注册用于获取关节状态的回调函数
     *        注册回调函数后,服务器实时推送当前的关节状态信息.
     * @param ptr   获取实时关节状态信息的函数指针，当ptr==NULL时，相当于取消回调函数的注册,取消该推送信息也可以通过该接口robotServiceSetRealTimeJointStatusPush进行。
     * @param arg   这个参数系统不做任何处理，只是进行了缓存，当回调函数触发时该参数会通过回调函数的参数传回。
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int  robotServiceRegisterRealTimeJointStatusCallback(RealTimeJointStatusCallback ptr, void  *arg);

    /**
     * @brief 根据接口板IO类型和名称获取IO状态
     * @param type     IO类型
     * @param name     IO名称
     * @param value    IO状态
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceGetBoardIOStatus(aubo_robot_namespace::RobotIoType type, std::string name, double &value);
    /**
     * @brief 根据接口板IO类型和名称设置IO状态
     * @param type     IO类型
     * @param name     IO名称
     * @param value    IO状态
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceSetBoardIOStatus(aubo_robot_namespace::RobotIoType type, std::string name, double value);

    /**
     * @brief 根据接口板IO类型和地址设置IO状态
     * @param type    IO类型
     * @param addr    IO地址
     * @param value   IO状态
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int robotServiceSetBoardIOStatus(aubo_robot_namespace::RobotIoType type, int    addr,      double value);


    //设置机械臂工具
    int robotServiceSetRobotTool(const aubo_robot_namespace::ToolInEndDesc &robotTool);

    void SetGlobalMoveEndMaxParams();
    void SetGlobalMoveJointMaxParams();

    /**
     * @brief 机械臂运动控制   停止,暂停,继续
     * @param cmd    控制命令
     * @return　调用成功返回ErrnoSucc;错误返回错误号
     */
    int  rootServiceRobotMoveControl(aubo_robot_namespace::RobotMoveControlCommand cmd);

    int setOffset(float x_offset, float y_offset, float z_offset);

    int moveJwithPose(double *pose, bool isBlock);
};


#endif //AUBOROBOTQT_ROBOT_H
