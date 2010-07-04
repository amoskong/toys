import java.io.IOException;
import javax.microedition.lcdui.* ;
import javax.microedition.lcdui.game.Sprite;

public class Bullet{ //子弹类
	private Image im_p;
	public Sprite p;
	public double x=0;
	public double y=0;
	public double fx2 = 0;
	public double fy2 = 0;
	public double vx = 0;
	public double vy = 0;

	public Bullet(){
		try {
			im_p = Image.createImage("/bullet.png");
			p=new Sprite(im_p);
		} catch (IOException e) {
			System.out.println(e);
		}
		
	}

}
