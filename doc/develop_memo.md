开发备忘录

### 2024122300

绘图改造。在frame中添加一个canvas，canvas中存在view，view中存在painter和entity，painter中
存在绘图接口指针绘制的时候，view中的entity表示绘制数据，painter中的绘图接口指针指向具体的绘图后
端view还记录缩放、视口等信息。

在canvas的PaintEvent中，通过view绘制所有entity。

实现一个绘图后端。view->painter->interface执行绘制，interface是图形绘制接口（基类指针），指向
具体的绘图后端，比方说cairo，每一次PaintEvent绘制，都创建cairo对象进行绘制，绘制结束后销毁对象，
类似win32 api的BeginPaint/EndPaint，在BeginPaint中创建对象，在EndPaint中销毁对象，可以将其
设计到一个类的构造和析构函数中，PaintEvent响应时创建这么个局部对象，在这个局部对象的生命周期内，通
view去调用具体的绘图后端进行绘制就是有效的了。

引入cairo绘图后端要解决一个问题，即当前OnPaint申请的绘图缓冲区尺寸是和当前窗口尺寸匹配的，如果窗口
尺寸发生变换也就是OnSize，需要重新为cairo绘图后端申请和变化后窗口尺寸匹配的绘图缓冲区，但是可能在
OnSize的时候，绘图缓冲区还在使用，为了避免冲突，要引入锁的机制，绘制时锁住绘图缓冲区，绘制完即释放
锁，以便OnSize去销毁并重新申请新的绘图缓冲区。

解决办法，在ctor中初始化绘图后端，在OnSize中重建缓冲区，在OnPaint中通过缓冲区进行绘制。

### 2024122400
绘图测试，生成随机线段进行绘图。还是有bug，窗口移动到桌面外，会崩溃。

### 2024122401
要把绘图后端（画布、上下文）拎出来，设想一个场景，我们需要一个绘图窗口，现在的做法是，通过加入view和
painter成员，view存放绘图数据，painter提供绘图接口（比如使用cairo绘图），使得一个窗口实例成为绘
窗口。我们可以把绘图后端独立出来，使得context和painter解耦。

cairo后端绘图结束时需要通过wxClientDC将bitmap绘制到窗口上，考虑将context类继承于wxWindow。

### 2024122700
要设计一个图元基类，将图元共同的操作提取到图元基类中，比如绘制接口，这样利用多态可以实现所有图元的绘制。

### 2024122800
重新回顾一下整个设计。drawpanel是跟具体ui框架相关的窗口，绘制发生在该窗口的客户区内，view存放绘图
据以及提供视口变换相关的功能（比如缩放、平移等），painter提供绘图接口，原定将图元的绘制逻辑放在painter
中，这样entity就不需要耦合绘图接口而只是提供图元数据，但是目前绘图接口放到了entity中，这样具体的绘
图逻辑就分散在了各个entity子类中，painter其实不再需要了。

window类不再直接管理context，改为，window管理view，view管理context和entity列表。
