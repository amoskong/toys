import java.awt.*;
import java.util.*;
import java.applet.*;
import java.awt.event.*;

import javax.swing.*;

class MouseClass 
{
	int     seed,stayTime;    //随机数用到的参数和地鼠停留的时间
	int		gameLevel,livingTime[];			//游戏等级和每种地鼠的存活时间
	int     X,Y,width,height;
	int     MouseNum,level;			//地鼠编号，游戏等级
	
	boolean visible;
	Image   MouseImage[],HitMouseImage,LaughMouseImage,Hole;		//地鼠图片,打中后的地鼠图片和地洞图片
	Applet  Game;          //引入Applet容器
	Random  R;             //声明随机数变量
	boolean showMouse,showHitMouse,showLaughMouse;		//判断是否可出现地鼠和打中后的地鼠的参数	

	public MouseClass(Image MouseImag[],Image HitMouseImage,Image LaughMouseImage,Image Hole,Applet Game)
	{
		R = new Random();
		MouseNum = 0;
		stayTime = 0;
		this.MouseImage = new Image[MouseImag.length];			//申请图片空间
		
		level = 1;					//设置默认难度 简单
		livingTime =	new int[MouseImag.length-3];			//申请int空间	
		livingTime[0]= 400;			
		livingTime[1]= 300;
		livingTime[2]= 500;
		livingTime[3]= 200;
		livingTime[4]= 100;
		livingTime[5]= 150;
		
		for(int i=0;i<MouseImag.length;i++)					//传入地鼠图片数组
			this.MouseImage[i]=MouseImag[i];
		
		this.HitMouseImage = HitMouseImage;			//打中后的地鼠
		this.LaughMouseImage = LaughMouseImage;			//笑的地鼠
		this.Hole       = Hole;				
		this.Game        = Game;
		
		showMouse	= false;	
		showHitMouse       = false;		
		showLaughMouse     = false;
		
		setVisible(true);		//设置可见，加入此参数为了可以让某个地洞和地鼠不可见，一般为所有地洞都显示出来
	}	
	public void setGameLevel(int gamelevel)
	{
		level=gamelevel;
		if(level==1)
		{
			livingTime[0]= 400;
			livingTime[1]= 300;
			livingTime[2]= 500;
			livingTime[3]= 200;
			livingTime[4]= 100;
			livingTime[5]= 150;
		}
		else if(level==2)
		{
			livingTime[0]= 250;
			livingTime[1]= 180;
			livingTime[2]= 400;
			livingTime[3]= 100;
			livingTime[4]= 100;
			livingTime[5]= 100;
		}
		else if(level==3)
		{
			livingTime[0]= 180;
			livingTime[1]= 150;
			livingTime[2]= 200;
			livingTime[3]= 80;
			livingTime[4]= 100;
			livingTime[5]= 70;
		}
	}
	public void setLocation(int X,int Y)   //定位
	{
	    this.X = X;
	    this.Y = Y;
	}
	public void setVisible(boolean v)
	{
	    visible = v;
	}
	public void updateState()		//改变地鼠状态的方法
	{
		//根据随机数来改变地鼠状态，出现的频率和停留的时间均可调节
		//这是一种简单的控制方法,如有更好的想法可改进此处
		if(!showMouse && !showLaughMouse && !showHitMouse)		//没有地鼠时执行
		{
			if(R.nextInt(seed) % 2000 < level*5)			//判断何时出现地鼠头像
			{
				showMouse = true;
				MouseNum = R.nextInt(5);
			}
			else if(R.nextInt(seed+1000)%3000 < 1)			//判断何时出现道具
			{
				showMouse = true;
				MouseNum = R.nextInt(4)+5;	
			}
		}			
		else if(showHitMouse && stayTime > 50)		//被打中的地鼠显示0.5秒
		{
			showHitMouse = false;
		}	
		
		if((showMouse || showLaughMouse))	//4种地鼠分别停留2秒，4秒，5秒，1秒
		{
			if(MouseNum == 0)
			{	
				if(stayTime > livingTime[0])
				{	
					showMouse = false;
					showLaughMouse = false;
				}
			}
			else if(MouseNum == 1)
			{
				if(stayTime > livingTime[1])
				{	
					showMouse = false;
					showLaughMouse = false;
				}
			}
			else if(MouseNum == 2)
			{
				if(stayTime > livingTime[2])
				{	
					showMouse = false;
					showLaughMouse = false;
				}
			}
			else if(MouseNum == 3)
			{
				if(stayTime > livingTime[3])
				{	
					showMouse = false;
					showLaughMouse = false;
				}
			}
			else if(MouseNum == 4)
			{
				if(stayTime > livingTime[4])
				{	
					showMouse = false;
					showLaughMouse = false;
				}
			}
			else			//注意，因为设定是1秒未打中则地鼠头像变为笑的图片，所以此处道具的停留时间最好不要大于1秒，否则会变成笑的图片
			{
				if(stayTime > livingTime[5])
				{	
					showMouse = false;
					showLaughMouse = false;
				}
			}
		}			
	}
	public int getMouseNum()
	{
	    return MouseNum;
	}
	public void setMouseNum(int MouseNum)
	{
		this.MouseNum = MouseNum;
	}
	//设置是否出现的方法
	public void setshowMouse(boolean showMouse)
	{
		this.showMouse = showMouse;
	}
	public void setshowHitMouse(boolean showHitMouse)
	{
		this.showHitMouse = showHitMouse;
	}
	public void setshowLaughMouse(boolean showLaughMouse)
	{
		this.showLaughMouse = showLaughMouse;
	}
	
	public void paintGame(Graphics g)
	{
		if(visible == true)
		{
			g.drawImage(Hole,X,Y,Game);			//绘制地洞图像，X,Y为坐标

			if(showMouse == true)				//根据showMouse参数判断是否绘制地鼠图像
				g.drawImage(MouseImage[MouseNum],X + 12,Y + 18,Game);
			else if(!showLaughMouse && showHitMouse )
				g.drawImage(HitMouseImage,X + 12,Y + 18,Game);
			else if(!showHitMouse && showLaughMouse)
				g.drawImage(LaughMouseImage,X + 12,Y + 18,Game);			
		}
	}

	public void setSeed(int seed)
	{
		this.seed = seed;
	}

	//判断是否击中的方法，参数依次为鼠标坐标，地鼠图片的长和高
	public boolean hit(int X,int Y,int MouseWidth,int MouseHeight)
	{
		if((this.X + MouseWidth >= X) && (this.Y + (MouseHeight) + 42>= Y) &&
				(X >= this.X) && (Y >= this.Y) && (showMouse || showLaughMouse))
		{
			if(MouseNum < 5 || showLaughMouse)			//如果打中的是地鼠
			{	
				//显示被打中的地鼠
				showMouse 		= false;
				showLaughMouse  = false;
				showHitMouse 	= true;
			}
			else				//如果是道具			
				showMouse = false;
			
			return true;
		}
		else
			return false;
	}
}

public class HitMouse extends JApplet
       implements Runnable,MouseListener,MouseMotionListener,ActionListener
{
	private static final long serialVersionUID = 1L;
	int         			AppletWidth,AppletHeight,HoleWidth,HoleHeight,
                			countX,countY,MouseWidth,MouseHeight,score,
                			GameSecond;   //游戏时间
	int        				CountTime,FlagTime,DoubleScoreTime,CoolHitTime,SequenceHit,SequenceCoolHit;		//用来记录时间的辅助变量,标志出现时间,双倍分数时间,记录暴击的辅助时间变量和连击次数,暴击次数
	AudioClip   			startSound,hitMouseSound,hitPropertySound,laughSound;		//开始音乐，打击的音效，笑声
    Image        			holeImage,hitMouseImage,laughMouseImage,Screen,SplitImage1,SplitImage2,bkImage;  
    Image					mouseImage[];	
    Thread       			newThread;			//添加线程
    Graphics     			drawScreen;     //声明Screen的Graphics对象
    MediaTracker 			MT;				//添加媒体追踪器，用来加载图像
    MouseClass    			mouseSprite[];		//地鼠对象
    
    Box 					boxV;				//box布局对象，放置按钮
    
    Font 					F1,F2,F3; 				//字体对象  
    
    JPanel        			Status1,Status2,MainPanel;		//游戏面板,显示连击的面板，主面板
  
    JLabel        			TimeTitle,ScoreTitle,showScoreTitle,SequenceHitTitle,SequenceCoolHitTitle;			//显示时间和分数,还有连击次数,连续次数暴击
    JButton      		 	settingButton,helpButton,pauseButton,endButton;				//开始和结束按钮
    boolean      			isStartGame,isEndGame,isPlayMusic,isAddControlPanel,isDoubleScore,showFlag,showSequenceHit;		//判断开始和结束,开始菜单的选项是否被选中，是否添加控制面板，是否是双倍游戏时间，还有显示标志，连击的参数
   
    StartScreen  			S_Screen;				//声明开始界面类的对象
    CloseDialog  			CD;					//声明结束对话框类的对象
    settingDialog 			setGame;
    
    String					helpWords;    //帮助文字
    
    Toolkit 				toolkit=Toolkit.getDefaultToolkit(); //得到默认的ToolKit对象
    Image 					hammerImage1=toolkit.getImage(Thread.currentThread().getContextClassLoader().getResource("sourcefile/HAMMER1.GIF")); //得到图像
	Image 					hammerImage2=toolkit.getImage(Thread.currentThread().getContextClassLoader().getResource("sourcefile/HAMMER2.GIF")); 
	Cursor 					hammerCursor1=toolkit.createCustomCursor(hammerImage1,new Point(0,30),"MyCursor1"); //自定义光标对象
	Cursor 					hammerCursor2=toolkit.createCustomCursor(hammerImage2,new Point(0,30),"MyCursor2");
    GregorianCalendar 		time;			//声明GregorianCalendar的对象，用来获取时间

    public void init()
    {
    	addMouseListener(this);				//给APPLET添加鼠标事件监听
    	addMouseMotionListener(this);		//给APPLET添加鼠标移动事件监听
    	this.setCursor(hammerCursor1);		//设置光标
        
   
    	AppletWidth    = 815;			//Applet宽和高，可调整
        AppletHeight   = 670;
    	 
        helpWords      = "猪头出现时用鼠标点击，打中目标加分，没打中不加分。\n" +
		   				 "0.3秒内打中为暴击，额外加5分。连续打中3次开始计\n" +
		   				 "连击次数，连续击中时间都在0.5秒内则为连暴击，2次连\n" +
		   				 "暴击开始计连暴击次数，根据连击和连暴击次数额外加分.\n" +
		   				 "连暴击加分非常多。点击暂停按钮暂停游戏。\n" +
		   				 "游戏中有种猪头，分别是痴呆猪，酷酷猪，凶恶猪和暴怒猪，\n" +
		   				 "4种猪头出现的时间依次递减，当然，打中的得分依次递增!\n" +
		   				 "还有一种伤员猪，是不能打的，打中扣分.另外还有4种道具\n" +
		   				 "作用分别是击打全屏幕所有出现的猪头；随机加一定的分\n" +
		   				 "(有小概率为负分);全屏出现伤员猪(副作用道具);十秒内\n" +
		   				 "所有应得分数翻倍!\n" +
		   				 "祝您愉快！";
        
        countX        = 3;								//水平方向地鼠个数
        countY        = 3;								//竖直方向地鼠个数
        score         = 0;								//分数	
        GameSecond    = 0;								//游戏时间
        CountTime     = 0;								//辅助计时的变量
        FlagTime     	= 0;
        DoubleScoreTime = 0;
        CoolHitTime		= 1;
        SequenceHit     = 0;
        SequenceCoolHit = 0;
        //以下是几个boolean类型值的初始化
        isStartGame     	= true;
        isEndGame       	= false;
        isPlayMusic			= true;
        isAddControlPanel   = true ;
        isDoubleScore  		= false;
        showFlag      		= false;
        showSequenceHit 	= false;
        
        //以下是控制面板数据初始化
        boxV=Box.createVerticalBox();				//竖直布局
    	
    	F1     = new Font("TimesRoman",Font.BOLD + Font.ITALIC,72);				//设置几种字体
    	F2     = new Font("TimesRoman",Font.BOLD + Font.ITALIC,50);
    	F3     = new Font("TimesRoman",Font.BOLD,15);
    	
    	CD     = new CloseDialog(this,new JFrame());		//初始化结束对话框
    	
    	time   = new GregorianCalendar();
    	
    	TimeTitle    = new JLabel("时间: 0");		//设置标签
    	TimeTitle.setFont(F3);
    	
    	showScoreTitle  = new JLabel("分数:  ");
    	showScoreTitle.setFont(F3);
    	ScoreTitle  = new JLabel("         0");
    	ScoreTitle.setFont(F2);
    	ScoreTitle.setForeground(Color.blue);
    	
    	SequenceHitTitle = new JLabel("");
    	SequenceHitTitle.setFont(F2);
    	SequenceHitTitle.setForeground(Color.ORANGE);
    	
    	SequenceCoolHitTitle = new JLabel("");
    	SequenceCoolHitTitle.setFont(F2);
    	SequenceCoolHitTitle.setForeground(Color.BLACK);
    	
    	endButton      = new JButton("结束游戏");
    	helpButton     = new JButton("游戏帮助");
    	settingButton  = new JButton("游戏设置");
    	pauseButton    = new JButton("暂停游戏");
    	pauseButton.setEnabled(false);				//暂停键初始不可点击
    	endButton.addActionListener(this);
    	settingButton.addActionListener(this);
    	helpButton.addActionListener(this);
    	pauseButton.addActionListener(this);
    	
    	//初始化面板
    	Status1   = new JPanel();
    	Status2   = new JPanel();
    	MainPanel = new JPanel(); 	
        Status1.setLayout(new GridLayout(3,1));
        Status2.setLayout(new GridLayout(2,1));
        MainPanel.setLayout(new GridLayout(3,1));
  
        Status1.add(TimeTitle);
        Status1.add(showScoreTitle);
        Status1.add(ScoreTitle);
      
        Status2.add(SequenceHitTitle);
        Status2.add(SequenceCoolHitTitle);
        
      	boxV.add(Box.createVerticalStrut(15));
        boxV.add(Box.createHorizontalStrut(30));
        boxV.add(settingButton);	
        boxV.add(Box.createHorizontalStrut(30));
        boxV.add(pauseButton);  
        boxV.add(Box.createHorizontalStrut(30));
        boxV.add(helpButton); 
        boxV.add(Box.createHorizontalStrut(30));       
        boxV.add(endButton);
        boxV.add(Box.createVerticalStrut(75));
        
        MainPanel.add(Status1);   
        MainPanel.add(Status2);      
        MainPanel.add(boxV);
 
        setLayout(new BorderLayout());    //设置applet布局
        
        //以下是声音文件的初始化
        hitMouseSound        = getAudioClip(Thread.currentThread().getContextClassLoader().getResource("sourcefile/hitMouseSound.wav"));
        hitPropertySound	 = getAudioClip(Thread.currentThread().getContextClassLoader().getResource("sourcefile/hitPropertySound.wav"));
        laughSound      	 = getAudioClip(Thread.currentThread().getContextClassLoader().getResource("sourcefile/piglaugh.wav"));
        startSound      	 = getAudioClip(Thread.currentThread().getContextClassLoader().getResource("sourcefile/kaitou.wav"));
        
        //以下是图片文件的初始化和加载
        
        mouseImage		   = new Image[9];
        mouseImage[0]      = getImage(Thread.currentThread().getContextClassLoader().getResource("sourcefile/pig.gif"));			//地鼠图片
        mouseImage[1]      = getImage(Thread.currentThread().getContextClassLoader().getResource("sourcefile/pig1.gif"));			//地鼠图片
        mouseImage[2]      = getImage(Thread.currentThread().getContextClassLoader().getResource("sourcefile/pig2.gif"));			//地鼠图片
        mouseImage[3]      = getImage(Thread.currentThread().getContextClassLoader().getResource("sourcefile/pig3.gif"));			//地鼠图片
        mouseImage[4]      = getImage(Thread.currentThread().getContextClassLoader().getResource("sourcefile/pig4.gif"));			//地鼠图片
        mouseImage[5]      = getImage(Thread.currentThread().getContextClassLoader().getResource("sourcefile/allhit.gif"));			
        mouseImage[6]      = getImage(Thread.currentThread().getContextClassLoader().getResource("sourcefile/radomscore.gif"));			
        mouseImage[7]      = getImage(Thread.currentThread().getContextClassLoader().getResource("sourcefile/allpig.gif"));			
        mouseImage[8]      = getImage(Thread.currentThread().getContextClassLoader().getResource("sourcefile/doublescore.gif"));
        
        hitMouseImage      = getImage(Thread.currentThread().getContextClassLoader().getResource("sourcefile/hitpig.gif"));			//打中后的地鼠图片
        laughMouseImage    = getImage(Thread.currentThread().getContextClassLoader().getResource("sourcefile/laughpig.gif"));		//笑的地鼠图片
        
        holeImage    	   = getImage(Thread.currentThread().getContextClassLoader().getResource("sourcefile/hole.png"));					//地洞图片
        
        SplitImage1        = getImage(Thread.currentThread().getContextClassLoader().getResource("sourcefile/pighead1.gif"));			//开始界面的飘动图片
        SplitImage2 	   = getImage(Thread.currentThread().getContextClassLoader().getResource("sourcefile/pighead2.gif"));
        bkImage        	   = getImage(Thread.currentThread().getContextClassLoader().getResource("sourcefile/back.jpg"));			//背景图片
        
        MT       = new MediaTracker(this);
        for(int i=0;i<mouseImage.length;i++)		//加载图片
        	MT.addImage(mouseImage[i],0);
        
        MT.addImage(hitMouseImage,0);
        MT.addImage(laughMouseImage,0);
        MT.addImage(holeImage,0);
        MT.addImage(SplitImage1,0);
        MT.addImage(SplitImage2,0);
        MT.addImage(bkImage,0);
        //加载图像
        try
        {
        	MT.waitForAll();
        }
        catch(InterruptedException E){ }

        HoleWidth  = holeImage.getWidth(this);      //地洞宽度
        HoleHeight = holeImage.getHeight(this);		//地洞高度

        mouseSprite   = new MouseClass[9];		//9个地鼠
        for(int i=0;i<9;i++)
        {
        	mouseSprite[i] = new MouseClass(mouseImage,hitMouseImage,laughMouseImage,holeImage,this);	//初始化地鼠对象
        	mouseSprite[i].setLocation(i%countX*HoleWidth,i/countY*HoleHeight);		//设置每个地鼠的坐标
        	mouseSprite[i].setSeed(2000);			
        	//设置产生随机数时要用到的辅助变量
        }

        MouseWidth    = mouseImage[0].getWidth(this);				//地鼠图片宽度
        MouseHeight   = mouseImage[0].getHeight(this);				//底数图片长度
        
        setGame     = new settingDialog(this,new JFrame());		//初始化游戏设置对话框
        S_Screen 	= new StartScreen(AppletWidth,AppletHeight,this,SplitImage1,SplitImage2,bkImage); //开始界面        
        Screen      = createImage(AppletWidth,AppletHeight);   //Screen为整个屏幕图像
        drawScreen  = Screen.getGraphics();     //初始化drawScreen
 
   
        resize(AppletWidth,AppletHeight);
    }
    public void addControlPanel()				//加入控制面板
    {      
        getContentPane().add(MainPanel,BorderLayout.EAST);
    }
    public void start()
    {
    	newThread = new Thread(this);		//start时初始化线程		
    	newThread.start();
    }

    public void stop()
    {
    	newThread = null;					//stop时释放线程  (这里有问题,为什么去掉这句就不正常了)
    }

    public void paint(Graphics g)
    {
    	drawScreen.clearRect(0,0,AppletWidth,AppletHeight);			//清屏   	
   	
    	if(isStartGame)
    	{
    		S_Screen.paintScreen(drawScreen);     //绘制开始界面 
    	}
    	else						//绘制游戏界面
    	{
    		for(int i=0;i<9;i++)
    			mouseSprite[i].paintGame(drawScreen);
    		if(showFlag)
    			paintFlag(drawScreen);
    	}
    	
    	g.drawImage(Screen,0,35,this);
    }
    public void paintFlag(Graphics g)
    {
    	g.setFont(F1);
    	g.setColor(Color.RED);
    	g.drawString("Cool !", 200, 300);
    }
    
    public void update(Graphics g)   //覆盖update方法，使其不清除原来图像而只是调用paint方法
    {
    	paint(g);
    }

    public void run()				//线程的run方法
    {
    	if(isStartGame && isPlayMusic)					//开始界面播放开始音乐
			startSound.loop();
    	
		while(newThread!= null)
    	{							   			
    		try
    		{
    			Thread.sleep(10);
    		}
    		catch(InterruptedException E){ }
    		
    		if(isStartGame)				//飘动图像  		
    		{	
    			S_Screen.UpdateStatus();   
    			if(!isPlayMusic)
    				startSound.stop();
    		}
    		else
    		{ 			
    			if(isAddControlPanel)		//进入游戏界面则加入控制面板
    			{
    				addControlPanel();
    				resize(HoleWidth*countX+220,HoleHeight*countY+70); 
    				
    			//	resize(AppletWidth,AppletHeight);   //调整大小,这里有问题
    				isAddControlPanel = false;
    			}	
    			
    			if(pauseButton.isEnabled()==false)		//暂停键设为可点击
    				pauseButton.setEnabled(true);
    			if(CountTime%100 == 0)					//设置时间,GameSecond每秒加1
    			{
    				GameSecond++;      				
    	
    				if(SequenceHit<3)		//连击次数小于3则清除显示,放到这里是因为想让它每秒判断一次，即显示时间至少为一秒
    				{	
    					SequenceHitTitle.setText("");	
    					showSequenceHit = false;
    				}
    				
    				if(SequenceCoolHit<2)		//连暴击小于2则清除显示
    				{	
    					SequenceCoolHitTitle.setText("");	
    				}
    			}   
    			if(CountTime > DoubleScoreTime)
    			{
    				DoubleScoreTime = 0;
    				isDoubleScore = false;
    			}
    			if(FlagTime > 100)
    			{
    				showFlag=false;      //Flag显示一秒
    				FlagTime = 0;
    			}
    			TimeTitle.setText("时间: " + GameSecond + "秒");   //显示时间
    			
    			if(showSequenceHit && SequenceHit>=3)		//大于等于3次连击显示连击次数
    			{
    				SequenceHitTitle.setText("\n\n\n"+SequenceHit+"连击!");
    			}
    			
    			if(SequenceCoolHit >= 2)		//大于等于2次连击显示连暴击次数
    			{
    				SequenceCoolHitTitle.setText("\n\n\n"+SequenceCoolHit+"暴击!");
    			}
    			
        		for(int i=0;i<9;i++)
    			{	
    				mouseSprite[i].updateState();		//地鼠变化状态
    				
    				//地鼠显示时stayTime++
    				if(mouseSprite[i].showMouse || mouseSprite[i].showHitMouse || mouseSprite[i].showLaughMouse)	
    					mouseSprite[i].stayTime++;
    				else		//没地鼠时停留时间清零
    					mouseSprite[i].stayTime=0;				
    			}
        		
        		for(int i=0;i<9;i++)
    			{
    				if(mouseSprite[i].stayTime > 150)  //停留时间大于1.5秒显示笑的地鼠
    				{
    					mouseSprite[i].setshowMouse(false);
    					mouseSprite[i].setshowLaughMouse(true);  
    					if(isPlayMusic)
    						laughSound.play();
    				}
    			}	
        		
    		}
    		
    		CountTime++;   //计时辅助参数++
    		if(showFlag)
    			FlagTime++;
    	}
    }

   public void setEndGame(boolean isEndGame)
   {
      this.isEndGame = isEndGame;
   }
   public void upDateScore(int i)			//更新分数的方法
   {
	   //4种地鼠根据出现时间的不同加不同的分
	   if(!isDoubleScore)     //是否是双倍得分时间
	   {
		   if(mouseSprite[i].getMouseNum() == 0)				
			   score += 10;	
		   else if(mouseSprite[i].getMouseNum() == 1)
			   score += 8;		
		   else if(mouseSprite[i].getMouseNum() == 2)
			   score += 5;		  
		   else if(mouseSprite[i].getMouseNum() == 3)
		   	   score += 15;				   
		   else if(mouseSprite[i].getMouseNum() == 4)
		   {  
			   score -= 20;		   
			   SequenceHit = 0;
		   }
	   }
	   else
	   {
		   if(mouseSprite[i].getMouseNum() == 0)				
			   score += 20;	
		   else if(mouseSprite[i].getMouseNum() == 1)
			   score += 16;		
		   else if(mouseSprite[i].getMouseNum() == 2)
			   score += 10;		  
		   else if(mouseSprite[i].getMouseNum() == 3)
		   	   score += 30;				   
		   else if(mouseSprite[i].getMouseNum() == 4)
		   {  
			   score -= 40;		   
			   SequenceHit = 0;
		   }
	   }
   }
   public void mouseExited(MouseEvent e){}
  
   public void mouseClicked(MouseEvent e)
   {
	   if(isStartGame)
	   {			
		   	if((e.getX() > S_Screen.ItemX && e.getX() < S_Screen.ItemX + S_Screen.ItemWidth) && 
		   			((e.getY() > S_Screen.ItemY+15+S_Screen.ItemCap) && 
				   			(e.getY() < S_Screen.ItemY+S_Screen.ItemCap+15+S_Screen.ItemHeigth)))
		   	{
		   		isStartGame = false;						   		
		   		startSound.stop();
				Screen      = createImage(AppletWidth-250,AppletHeight);   //Screen为整个屏幕图像
        		drawScreen  = Screen.getGraphics();     //初始化drawScreen		
		   	} 
		   	else if((e.getX() > S_Screen.ItemX && e.getX() < S_Screen.ItemX + S_Screen.ItemWidth) && 
		   			((e.getY() > S_Screen.ItemY+S_Screen.ItemHeigth+15+S_Screen.ItemCap) && 
				   			(e.getY() < S_Screen.ItemY+S_Screen.ItemHeigth+15+S_Screen.ItemCap+S_Screen.ItemHeigth)))
		   	{
		   		setGame.setVisible(true);
		   	} 	
		   	else if((e.getX() > S_Screen.ItemX && e.getX() < S_Screen.ItemX + S_Screen.ItemWidth) && 
		   			((e.getY() > S_Screen.ItemY+S_Screen.ItemHeigth*2+15+S_Screen.ItemCap) && 
				   			(e.getY() < S_Screen.ItemY+S_Screen.ItemHeigth*2+15+S_Screen.ItemCap+S_Screen.ItemHeigth)))
		   	{
		   		JOptionPane.showMessageDialog(this,helpWords,"帮助",JOptionPane.INFORMATION_MESSAGE);
		   	} 	
		   	if((e.getX() > S_Screen.ItemX && e.getX() < S_Screen.ItemX + S_Screen.ItemWidth) && 
		   				((e.getY() > S_Screen.ItemY+15+S_Screen.ItemHeigth*3+S_Screen.ItemCap) && 
				   				(e.getY() < S_Screen.ItemY+15+S_Screen.ItemHeigth*3+S_Screen.ItemCap+S_Screen.ItemHeigth)))
		   	{
		   		System.exit(0);
		   	} 		
	   }
	   
   }

   public void mouseEntered(MouseEvent e)
   {
	   showStatus("X:" + e.getX() + "," + "Y:" + e.getY());
   }

   public void mousePressed(MouseEvent e)
   {
	   if(isStartGame) return;				//开始界面点击鼠标无效
	   this.setCursor(hammerCursor2);		//点击变化光标
	 
	   int X = e.getX();
	   int Y = e.getY();
	   showSequenceHit = false;	      
	   
	   for(int i=0;i<9;i++)
	   {
		   if(mouseSprite[i].hit(X,Y,MouseWidth, MouseHeight) == true)
		   {			   
			   if(mouseSprite[i].getMouseNum() < 5 && isPlayMusic)				//判断播放砸中地鼠的声音还是砸中道具的声音
				   hitMouseSound.play();
			   else if(mouseSprite[i].getMouseNum() >= 5 && isPlayMusic)
				   hitPropertySound.play();
			   			   
			   if(mouseSprite[i].showLaughMouse)			//停止笑声
				   laughSound.stop();
			   
			   if((CountTime - CoolHitTime) < 50)		//连续打中并且都在0.5秒内打中则计连暴击
				   SequenceCoolHit++;			//暴击次数加1
			   else
				   SequenceCoolHit = 0 ;			//没在0.5秒内打中则连暴击次数清零
			   
			   CoolHitTime = CountTime;
			   
			   if(mouseSprite[i].stayTime < 50)			//0.5秒内打中显示cool并额外加分
			   {
				   showFlag=true;
				   if(!isDoubleScore)
					   score += 5;
				   else
					   score += 10;
			   }
			   
			   mouseSprite[i].stayTime = 0;  //被打中则停留时间清零
			   
			   upDateScore(i);				//根据情况更新分数
			   
			   if(mouseSprite[i].getMouseNum() == 5)		//全打道具，把全屏幕能得分的地鼠全打
			   {  
				   	for(int j=0;j<9;j++)
				   	{				   
				   		if(mouseSprite[j].showMouse || mouseSprite[j].showLaughMouse)
				   		{
				   			if(mouseSprite[j].getMouseNum() < 4)
				   			{
				   				mouseSprite[j].showMouse = false;
				   				mouseSprite[j].showLaughMouse = false;
				   				mouseSprite[j].showHitMouse = true;
				   				if(isPlayMusic)
				   					hitMouseSound.play();
				   				
				   				upDateScore(j);				//根据情况更新分数
				   				
				   				mouseSprite[j].stayTime = 0;		//被打中，停留时间清零
				   			}   
				   		}		
				   	}
		 
			   }
			  
			   else if(mouseSprite[i].getMouseNum() == 6)		//随机加分的道具
			   {  
				   Random r		=	new Random();
				   score 		-=  r.nextInt(200)-30;			   //有较小概率减分
				   if(!isDoubleScore)
					   score    += r.nextInt(200)-30;
				   else
					   score    += (r.nextInt(200)-30)*2;
			   }			   
			   else if(mouseSprite[i].getMouseNum() == 7)		
			   {  		
				   for(int j=0;j<9;j++)
				   {					   	
					   	mouseSprite[j].setMouseNum(4);
					   	mouseSprite[j].showMouse = true;
	   					mouseSprite[j].showLaughMouse = false;
	   					mouseSprite[j].showHitMouse = false;
	   					mouseSprite[j].stayTime = 0;
				   }
			   }
			   else if(mouseSprite[i].getMouseNum() == 8)		
			   {  
				   isDoubleScore 	= true;
				   DoubleScoreTime 	= CountTime + 1000;			//10秒双倍分数时间
			   }
			   
			   if(SequenceHit>=3)	
				   score += SequenceHit*2;				//根据连击次数额外加分
			  
			   if(SequenceCoolHit>=2)	
				   score += SequenceCoolHit*10;				//根据连暴击次数额外加分
			   
			   ScoreTitle.setText("  "+score);
			   
			   showSequenceHit = true;
			   SequenceHit++;			//连击次数加1
		   }
	   }
	   if(showSequenceHit==false)		//没打中则连击次数清零,连暴击次数清零
	   {	
		   SequenceHit		= 0;	   		 
		   SequenceCoolHit  = 0;
	   }
   }

   public void mouseReleased(MouseEvent e)
   {
	   if(isStartGame) return;
	   this.setCursor(hammerCursor1);
   }

   public void mouseMoved(MouseEvent e)
   {
	   if(isStartGame)			//鼠标移到的菜单项变黄色
	   {	
		   for(int i=0;i<S_Screen.isItemSelect.length;i++)
		   {
		   		if((e.getX() > S_Screen.ItemX && e.getX() < S_Screen.ItemX + S_Screen.ItemWidth) && 
		   				((e.getY() > S_Screen.ItemY+15+S_Screen.ItemHeigth*i+S_Screen.ItemCap) && 
				   				(e.getY() < S_Screen.ItemY+15+S_Screen.ItemHeigth*i+S_Screen.ItemCap+S_Screen.ItemHeigth)))
		   		{
		   			S_Screen.isItemSelect[i]=true;
		   		} 	
		   		else
		   			S_Screen.isItemSelect[i]=false;
		   }
	   }
	   showStatus("X:" + e.getX() + "," + "Y:" + e.getY());
   }

   public void mouseDragged(MouseEvent e){} 

   public void actionPerformed(ActionEvent e)
   {
	   if(e.getSource() == settingButton)
	   {	   
		   newThread = null;		
		   setGame.setVisible(true);		   
		   newThread = new Thread(this);
		   newThread.start();	
	   }
	   else if(e.getSource() == pauseButton)
	   {
		   if(pauseButton.getText()=="暂停游戏")
		   {
			   newThread = null;
			   pauseButton.setText("继续游戏");
		   }
		   else
		   {   
			   	pauseButton.setText("暂停游戏");
			   	newThread = new Thread(this);
		   		newThread.start();
		   }	   
	   }
	   else if(e.getSource() == helpButton)
	   {
		   newThread = null;
		   JOptionPane.showMessageDialog(this,helpWords,"帮助",JOptionPane.INFORMATION_MESSAGE);
		   newThread = new Thread(this);
	   	   newThread.start();
	   }
	   else if(e.getSource() == endButton)
	   {		  
		   newThread = null;		
		   CD.setVisible(true);
		   
		   newThread = new Thread(this);
		   newThread.start();	   
	   }
   	}
   	public void clearData()			//数据恢复初始值
   	{
   		score         = 0;								//分数	
      	GameSecond    = 0;								//游戏时间
      	CountTime     = 0;								//辅助计时的变量
      	FlagTime     	= 0;
      	DoubleScoreTime = 0;
      	CoolHitTime		= 1;
       	SequenceHit   = 0;
       	SequenceCoolHit = 0;
       	//以下是几个boolean类型值的初始化
       	isStartGame     	= true;
       	isEndGame       	= false;
       	isAddControlPanel 	= true ;
       	isDoubleScore  		= false;
       	showFlag      		= false;
       	showSequenceHit 	= false;
	    Screen      		= createImage(AppletWidth,AppletHeight);   //Screen为整个屏幕图像
        drawScreen  		= Screen.getGraphics();     //初始化drawScreen	
       	getContentPane().remove(MainPanel);	
      
        resize(AppletWidth,AppletHeight);   //调整大小	  
   	}
}

class StartScreen
{
	int     width,height,StringWidth,StringHeight,Ascent,Descent,X,Y;
	int     ImageLeftBound,ImageRightBound,ImageX,ImageY,ImageWidth,
			ImageHeight,VX;
	int 	ItemX,ItemY,ItemWidth,ItemHeigth,ItemCap;		//菜单项横坐标，纵坐标，长度，高度，垂直间隔
	Font    F1,F2,F3;
	Image   Normal,Hit,currentImage,bkImage;
	String  ChineseTitle,EnglishTitle,PressEnter,ItemString[];	//标题和菜单项字符串
	Applet  Game;
	Random  R;
	boolean showPressEnter,isItemSelect[];			//菜单项是否被选中
	FontMetrics FM;   //此处定义FontMetrics对象，便于获取字体数据

	public StartScreen(int AppletWidth,int AppletHeight,HitMouse Game,Image normal,Image hit, Image bk)
	{
		R      = new Random();

		F1     = new Font("TimesRoman",Font.BOLD,72);
		F2     = new Font("TimesRoman",Font.BOLD + Font.ITALIC,36);
		F3     = new Font("TimesRoman",Font.BOLD,20);

		ChineseTitle    = "打猪头";
		EnglishTitle    = "Hit Pig's Head";

		width           = AppletWidth;
		height          = AppletHeight;
      
		Normal          = normal;				//初始状态下的飘动图像
		Hit             = hit;				//撞墙之后的飘动图像
		bkImage         = bk;					//背景图

		ImageWidth      = Normal.getWidth(Game);	//飘动图像的宽，Game是ImageObserver,勿混淆
		ImageHeight     = Normal.getHeight(Game);
		ImageLeftBound  = 0;					//飘动图像左边界
		ImageRightBound = Game.bkImage.getWidth(Game) -160;		//飘动图像右边界
		ImageX          = ImageRightBound;	//飘动图像起始横坐标，从右往左飘（可更改）

		ItemCap = 5 ;			//菜单项间隔设为25
		
		VX              = -1;				//用来控制飘动速度的参数
		this.Game       = Game;
		currentImage    = Normal;				//当前飘动的图像
		
		ItemString = new String[4];
		ItemString[0] = "开 始 游 戏";
		ItemString[1] = "游 戏 设 置";
		ItemString[2] = "游 戏 帮 助";
		ItemString[3] = "退 出 游 戏";
		
		showPressEnter  = true;
		isItemSelect = new boolean[4]; 
		isItemSelect[0]   = false;
		isItemSelect[1]   = false;
		isItemSelect[2]   = false;
		isItemSelect[3]   = false;
	}

	public void UpdateStatus()		//改变飘动图像
	{
		ImageX = ImageX + VX;			//通过参数VX变换飘动图像横坐标

		if(ImageX <= ImageLeftBound)			//撞左边界
		{
			currentImage = Hit;				//变化飘动图像

			ImageX = ImageLeftBound;			//飘动图像横坐标等于左边界横坐标
			VX     = -VX;						//参数取反
		}

		if(ImageX >= ImageRightBound)		//撞右边界，内容雷同撞左边界
		{
			currentImage = Normal;

			ImageX = ImageRightBound;
			VX     = -VX;
		}
	}

	public void paintScreen(Graphics g)
	{
		g.setFont(F1);
		FM = g.getFontMetrics();               //获取字体规格对象

		Ascent       = FM.getAscent();          //基线到字体顶部的距离
		Descent      = FM.getDescent();		   //基线到字体底部的距离
		StringWidth  = FM.stringWidth(ChineseTitle);			//获取字符串长度（注意是长度不是字符的个数）
		StringHeight = Ascent + Descent;						//获取字体高度

		X            = (width - StringWidth) / 2;				//定义大标题横坐标
		Y            = Ascent;								//定义大标题纵坐标（可自由调整）

		g.drawImage(bkImage, 0, 0, Game);					//绘制背景图
		g.setColor(Color.white);							//设置笔刷颜色
     
		g.drawString(ChineseTitle,X,Y); 					//写大标题	

		Y            = StringHeight;
		g.drawLine(X,Y,X+StringWidth,Y);					//画直线

		X            = X + 30;
		Y            = Y + 5;
		g.drawLine(X,Y,X+StringWidth-60,Y);		//画直线     

		g.setFont(F2);					//说明同上，换字体绘制EnglishTitle
		FM = g.getFontMetrics();

		Ascent       = FM.getAscent();
		Descent      = FM.getDescent();
		StringWidth  = FM.stringWidth(EnglishTitle);
		StringHeight = Ascent + Descent;

		X            = (width - StringWidth) / 2;
		Y            = Y + Ascent;
		g.drawString(EnglishTitle,X,Y);

		g.setFont(F3);				//菜单项
		FM = g.getFontMetrics();
		Ascent       = FM.getAscent();
		Descent      = FM.getDescent();
		ItemWidth    = FM.stringWidth(ItemString[0]);
		ItemHeigth 	 = Ascent + Descent;

		ItemX        = (width - ItemWidth)/2 ;
		ItemY        = height - 150;
		for(int i=0;i<isItemSelect.length;i++)
		{
			if(!isItemSelect[i])				//选中的菜单项变为黄色，正常状态为白色
	    		g.setColor(Color.white);
	    	else
	    		g.setColor(Color.yellow);
	  
	    	g.drawString(ItemString[i], ItemX, ItemY+ItemHeigth*i+ItemCap);	    	
		}
				
		ImageY       =  150;			//飘动图像纵坐标
		g.drawImage(currentImage,ImageX,ImageY,Game);			//绘制飘动图像
	}
}

class CloseDialog extends JDialog implements ActionListener   //结束对话框
{  
	private static final long serialVersionUID = 1L;
	Panel        P1,P2;
    Button       B1,B2;
    HitMouse	 Game;

    public CloseDialog(HitMouse Game,JFrame owner)
    {
    	super(owner,"离开游戏...",true);

    	this.Game = Game;

    	setLayout(new GridLayout(2,1));
    	P1 = new Panel();
    	P2 = new Panel();

    	P1.add(new Label("退出游戏?"));
    	P2.add(B1 = new Button("确定"));
    	P2.add(B2 = new Button("取消"));
    	B1.addActionListener(this);
    	B2.addActionListener(this);

    	getContentPane().add(P1);
    	getContentPane().add(P2);
    	pack();
    }

    public void actionPerformed(ActionEvent e)
    {
    	if(e.getSource() == B1)
    	{
    		Game.setEndGame(true);
    		Game.clearData();
    		setVisible(false);
    	}
    	else if(e.getSource() == B2)
    	{	Game.setEndGame(false);
    		setVisible(false);
    	}
    }
}

class settingDialog extends JDialog implements ItemListener,ActionListener   //游戏设置对话框
{  
	private static final long serialVersionUID = 1L;
	int gameLevel;
	boolean playMusic;
	JPanel        P1,P2,P3;
	JLabel		levelLabel, musicSetLabel;
	JRadioButton levelButton1,levelButton2,levelButton3,musicOnButton,musicOffButton;
	JButton    confirmButton,cancelButton;
	ButtonGroup levelGroup,musicSetGroup;
    HitMouse	 Game;
    
    public settingDialog(HitMouse Game,JFrame owner)
    {
    	super(owner,"游戏设置",true);
    	this.Game = Game;
    	
    	confirmButton = new JButton("确定");
    	cancelButton  = new JButton("取消");
    	confirmButton.addActionListener(this);
    	cancelButton.addActionListener(this);
    	
    	gameLevel = 1;				//默认难度为简单，音乐为开
    	playMusic = true;
    	
    	P1 = new JPanel();  
    	P2 = new JPanel();   
    	P3 = new JPanel();
    	
    	setLayout(new GridLayout(3,1));				//3行每行一个面板
    	levelLabel 		= new JLabel("请选择难度");
    	musicSetLabel   = new JLabel("是否打开音效");
    	
    	levelGroup=new ButtonGroup();					//难度选择
    	levelButton1=new JRadioButton("简单");
    	levelButton2=new JRadioButton("中等");   	
    	levelButton3=new JRadioButton("困难"); 
    	levelButton1.addItemListener(this);
    	levelButton2.addItemListener(this);
    	levelButton3.addItemListener(this);
    	levelGroup.add(levelButton1);
    	levelGroup.add(levelButton2);
    	levelGroup.add(levelButton3);
    	
    	musicSetGroup=new ButtonGroup();				//是否打开音乐
    	musicOnButton=new JRadioButton("开");
    	musicOffButton=new JRadioButton("关"); 
    	musicOnButton.addItemListener(this);
    	musicOffButton.addItemListener(this);
    	musicSetGroup.add(musicOnButton);
    	musicSetGroup.add(musicOffButton);
    
    	P1.add(levelButton1);
    	P1.add(levelButton2);
    	P1.add(levelButton3);
    	P2.add(musicOnButton);
    	P2.add(musicOffButton);
    	P3.add(confirmButton);
    	P3.add(cancelButton);
    	
    	getContentPane().add(levelLabel);
    	getContentPane().add(P1);
    	getContentPane().add(musicSetLabel);
    	getContentPane().add(P2);
    	getContentPane().add(P3);
    	pack();
    }
	
	public void itemStateChanged(ItemEvent arg0) 
	{
		if(arg0.getItemSelectable() == levelButton1)
		{
			gameLevel = 1;			
		}
		else if(arg0.getItemSelectable() == levelButton2)
		{
			gameLevel = 2;			
		}
		else if(arg0.getItemSelectable() == levelButton3)
		{
			gameLevel = 3;
		}
		
		if(arg0.getItemSelectable() == musicOnButton)
			playMusic=true;
		else if(arg0.getItemSelectable() == musicOffButton)
			playMusic=false;
	}

	public void actionPerformed(ActionEvent arg0) 
	{
		if(arg0.getSource() == confirmButton)
		{
			for(int i=0;i<Game.mouseSprite.length;i++)		//设置难度和音乐开关
			{		
				Game.mouseSprite[i].setGameLevel(gameLevel);					
			}
			
			if(Game.isStartGame && !Game.isPlayMusic && playMusic)		//开始界面从没声音调到有声音时BUG的解决
				Game.startSound.loop();
			
			Game.isPlayMusic = playMusic;
			setVisible(false);
		}
		else if(arg0.getSource() == cancelButton)
		{
			setVisible(false);
		}
		
	}
   
}