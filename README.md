# Intelligent-Sign-in-Management-system-based-on-Face-Recognition
This project named "Intelligent-Sign-in-Management-system-based-on-Face-Recognition",its from "National Innovation and Entrepreneurship Training Program for College Students(201912746003)"。
国家级大学生创新创业训练计划项目  基于人脸识别的实践教学管理平台（201912746003）
项目开发环境为 Qt 5.0以上编译器，依赖OpenCV3.0以上库，虹软SDK库。
本项目所依赖的OpenCV库以及虹软提供的SDK，您可前往OpenCV官网进行下载https://opencv.org/，所需版本为3.0以上，虹软SDK您可通过访问https://www.arcsoft.com.cn/ 来注册账号并下载相对应的SDK，版本为C++版x86 2.2.您也可以通过访问https://pan.baidu.com/s/1CGOpZB_-EmY-7-nBWho62A 来获取以上的依赖库。
请在项目src文件目录下将ArcSoftFaceUtils.cpp中相应的APPID和SDKKey更换为您的相应信息。
编译后初次使用系统需要进行管理员登录，生成认证文件后方可使用签到机认证功能，签到以及管理员刷脸登录需要先进行签到机认证。系统支持活体检测，有效避免照片、视频、纸张的欺骗，支持RGB以及IR活体检测，IR活体检测需要摄像硬件支持。特征值默认大小为1032KB，存储在数据库中需以BLOB格式保存，切勿使用string类型，不同系统存储特征值需要注意格式转换。
如您在使用以及开发过程中有更好的建议或反馈，您可联系我们，邮箱为：2650822367@qq.com & zxZhao1998@gmail.com

                                             
                                      CopyRight by Qiyao Dai & Zixuan Zhao (2020)
