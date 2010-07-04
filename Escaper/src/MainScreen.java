import javax.microedition.lcdui.* ;
import javax.microedition.lcdui.game.GameCanvas;
import javax.microedition.lcdui.game.LayerManager;
import javax.microedition.lcdui.game.Sprite;

public class MainScreen extends GameCanvas implements CommandListener
{
	private static Displayable instance ;
	LayerManager lm,lm2,lm3;
	Sprite man,man2,man3;
	Graphics g;
	int w, j, k, l, bn=0, exit=1;

	synchronized public static Displayable getInstance()
	{
		if(instance == null)
			instance = new MainScreen();
		return instance ;
	}
	public MainScreen()
	{
		super(false);

		g=this.getGraphics();
		addCommand(new Command("退出",Command.EXIT,1)) ;
		setCommandListener(this) ;
		keyPressed(-1);
		Navigator.hard.setValue(2);
	}
	public void commandAction(Command c,Displayable s)
	{
		Navigator.flow(c.getLabel());
	}
	public void keyPressed(int keyCode){
		if((keyCode == -1)&&bn>0){
			bn = bn - 1;
		}else if((keyCode== -2)&&bn<3){
			bn = bn + 1;
		}

		try
		{
			lm = new LayerManager();
			Image img = Image.createImage("/back.png");
			man = new Sprite(img);
			lm.append(man);            
			lm.paint(g,0,0);

			lm2 = new LayerManager();   	
			Image img2 = Image.createImage("/button.png");        	
			man2 = new Sprite(img2);        	
			lm2.append(man2);
			int Y=70;
			w=getWidth();j=getHeight();k=img2.getWidth();l=img2.getHeight();               	        	
			if (bn==0)
				lm2.paint(g,w/2-k/2,(j-160)/2+Y);
			if (bn==1)
				lm2.paint(g,w/2-k/2,(j-160)/2+28+Y);
			if (bn==2)
				lm2.paint(g,w/2-k/2,(j-160)/2+56+Y);
			if (bn==3)
				lm2.paint(g,w/2-k/2,(j-160)/2+84+Y);

			flushGraphics();
		}
		catch (Exception e){ }

		String cmd="null";
		if(keyCode==-5){
			switch(bn){
				case 0: cmd = "开始游戏";break; 	        		
				case 1: cmd = "游戏设置";break;
				case 2: cmd = "高分排榜";break;
				case 3: cmd = "游戏说明";break;
			}
		}
		Navigator.flow(cmd) ;
	}
}


