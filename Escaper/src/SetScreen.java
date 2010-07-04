import javax.microedition.lcdui.* ;

public class SetScreen extends Form implements CommandListener
{
	private static Displayable instance ;
	synchronized public static Displayable getInstance()
	{
		if(instance == null)
			instance = new SetScreen() ;
		
		return instance ;
	}
	
	TextField url ;

	private SetScreen()
	{
		super("游戏设置") ;
		append(Navigator.hard);
		append(Navigator.volme);
		url = new TextField("请输入姓名：","超级大玩家",8,TextField.URL) ;
		append(url) ;

		addCommand(new Command("返回",Command.BACK,1)) ;
		setCommandListener(this) ;
	}
	public void commandAction(Command c,Displayable s)
	{
		Navigator.flag=0;
		Navigator.flow(c.getLabel()) ;
	}
}
