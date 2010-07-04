import javax.microedition.midlet.*;
import javax.microedition.lcdui.*;

public class Escaper extends MIDlet
{
	boolean init = true ;
	public Escaper()
	{
		Navigator.display = Display.getDisplay(this) ;
		Navigator.midlet = this;
	}
	public void startApp()
	{
		Navigator.current = Navigator.MAIN_SCREEN ;
		Navigator.show(null) ;

		if(init)
		{
			Alert al = new Alert("Ã”Õˆ’ﬂ”Œœ∑") ;
			al.setType(AlertType.CONFIRMATION) ;
			al.setTimeout(10) ;
			Navigator.display.setCurrent(al) ;
			init = false ;
		}
	}
	public void pauseApp()
	{
	}
	public void destroyApp(boolean con)
	{
	}
}
