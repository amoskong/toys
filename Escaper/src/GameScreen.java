import java.util.Date;
import java.util.Random;
import javax.microedition.lcdui.* ;
import javax.microedition.lcdui.game.GameCanvas;
import javax.microedition.lcdui.game.LayerManager;
import javax.microedition.lcdui.game.Sprite;

public class GameScreen extends GameCanvas implements Runnable , CommandListener{
	private static Displayable instance ;
	synchronized public static Displayable getInstance()
	{
		if(instance == null)
			instance = new GameScreen() ;

		flag=Navigator.flag;
		if (flag==3) flag=0;
		if (flag==2){ 
			flag=1;
			d=new Date();
			d2=d.getTime();
			d1=d2-d1;
		}
		return instance ;
	}
	public static boolean conti = true;
	private int rate = 30; //控制刷新频率
	private Graphics g;
	public int getWidth=getWidth(); 
	public int getHeight=getHeight(); 
	//手机屏幕宽高常量，方便后面使用

	private GameScreen()
	{
		super(false);
		g = this.getGraphics();	
		g.setColor(0x00000);
		g.fillRect(0, 0, getWidth, getHeight);
		addCommand(new Command("返回",Command.BACK,1)) ;
		setCommandListener(this) ;

		random = new Random();
		start();
	}
	public void commandAction(Command c,Displayable s)
	{	
		Navigator.flag=flag;
		if (flag==3) flag=0;
		else if (flag==1){ 
			d=new Date();
			d2=d.getTime();
			d1=d2-d1;
			flag=2;
		}else flag=2;

		Navigator.flow(c.getLabel()) ;
	}	

	LayerManager lm_fly;
	Sprite fly;
	Bullet[] Bul;
	private double fx = getWidth/2;
	private double fy = getHeight/2;
	private double fx2 = 0;
	private double fy2 = 0;
	private double x = 0;
	private double y = 0;
	static int flag=0; //0 first 1 第2次 2 暂停 3 碰撞  

	static int MAX=0; //游戏设置难度对应的子弹数目
	int MAX2=2;
	int MAX_ALL=95; //难度最大时，生成子弹的数目

	int n=0;
	double L=0; //子弹到运动点的距离
	Random random;
	static Date d;
	static long d1=0; //游戏开始的时间
	static long d2=0; //游戏结束的时间 

	public double getxy(int x){  //随机得到一个0~x的double数	
		double p;	
		p=Math.abs(random.nextDouble()*1000)%x;
		return p;
	}
	public int getintxy(int x){  //随机的到一个0~x的int
		int p;

		if (x==0){ p=Math.abs(random.nextInt()); return p;}
		return random.nextInt(x);
	}
	public void run(){	

		long st;
		long et;
		lm_fly=new LayerManager();
		int i=0;
		Bul=new Bullet[MAX_ALL];
		for(i=0;i<MAX_ALL;i++){ 
			Bul[i]=new Bullet();
		}
		try { 
			Image im_fly = Image.createImage("/fly.png");
			fly=new Sprite(im_fly);
		}catch(Exception e){System.out.println(e); }			

		lm_fly.append(fly);
		for(i=0;i<MAX_ALL;i++){
			lm_fly.append(Bul[i].p);
		}

		while(conti){
			if (flag==2||flag==3){ //发生碰撞或暂停时
				continue;
			}
			else if (flag==0){ //第一次要做特殊处理，初始每个子弹的位置
				d=new Date();
				d1=d.getTime();
				MAX=Navigator.hard.getValue()*15+20;

				for(i=0;i<MAX_ALL;i++){
					rand(Bul[i]);
				}
				flag=1;
				fx=getWidth/2;
				fy=getHeight/2;
			}
			n=n%MAX2;
			n++;
			st = System.currentTimeMillis();

			input();			
			render(g);			
			for(i=0;i<MAX;i++){ 
				check(Bul[i]);
			}
			et = System.currentTimeMillis();				
			if((et - st) < rate){
				try{
					Thread.sleep(rate - (et -st));
				}catch(Exception e){System.out.println(e);}
			}
		}
	}

	public void rand(Bullet B){  //随机初始化子弹的位置

		fx2=getintxy(getHeight);
		fy2=getintxy(getHeight);
		int p=getintxy(0)%4;
		switch(p){	
			case 1: B.x=getWidth+5;B.y=getxy(getHeight);break; //屏幕右边框
			case 2: B.x=getxy(getWidth);B.y=-5;break; //屏幕上边框
			case 0: B.x=-5;B.y=getxy(getHeight); break; //屏幕左边框
			case 3: B.x=getxy(getWidth);B.y=getHeight+5;break; //屏幕下边框		
		}		
		B.fx2=fx2; B.fy2=fy2; //确定随机靠近点位置
		L=Math.sqrt((B.fx2-B.x)*(B.fx2-B.x)+(B.fy2-B.y)*(B.fy2-B.y)); //计算两点距离
		B.vx=(B.fx2-B.x)/L; //计算水平速度
		B.vy=(B.fy2-B.y)/L; //计算垂直速度
	}
	public void check(Bullet B){ //检测子弹出边界、碰撞等情况

		x=B.x;
		y=B.y;

		if (n==1){ //设置跟踪点
			fx2 = fx;//+getintxy(getWidth/4)-getWidth/8;
			fy2 = fy;//+getintxy(getHeight/4)-getHeight/8;
			B.fx2=fx2; B.fy2=fy2;
		}				
		if(x<-10||y<-10||x>getWidth+10||y>getHeight+10){ //子弹越界
			rand(B);			
		}
		if(fly.collidesWith(B.p, true)){ //发生碰撞

			flag=3;	
			d=new Date();
			d2=d.getTime();

			g.fillRect(0, 0, getWidth, getHeight);
			g.setColor(0xFFFFFF);
			g.drawString("成绩为: "+(double)((double)(d2-d1))/1000+" 秒",getWidth/2-40,getHeight/2,0);			
			flushGraphics();		
		}else{
			B.x+=1.5*B.vx;
			B.y+=1.5*B.vy;
		}		
	}

	public void render(Graphics g){			
		g.setColor(0x00000);
		g.fillRect(0, 0, getWidth, getHeight);

		int i=0;
		for(i=0;i<MAX_ALL;i++)
			Bul[i].p.setPosition((int)Bul[i].x,(int) Bul[i].y);
		//Bul[i].p.move((int)Bul[i].vx,(int)Bul[i].vy);

		fly.setPosition((int)fx, (int)fy);
		lm_fly.paint(g,0,0);
		flushGraphics();
	}

	public void input(){
		int keyState = getKeyStates(); //监听键盘
		if(((keyState & UP_PRESSED) != 0)&&fy>0){
			fy = fy - 1.9;
		}
		if(((keyState & DOWN_PRESSED) != 0)&&fy<getHeight-12){
			fy = fy + 1.9;
		}
		if(((keyState & LEFT_PRESSED) != 0)&&fx>0){
			fx = fx - 1.9;
		}
		if(((keyState & RIGHT_PRESSED) != 0)&&fx<getWidth-14){
			fx = fx + 1.9;
		}		
	}

	public void start(){ //启动线程
		Thread t = new Thread(this);
		t.start();
	}	
	public void record(){
		System.out.println("record");
	}

}

