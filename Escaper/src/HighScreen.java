import javax.microedition.lcdui.* ;

public class HighScreen extends Form implements CommandListener
{
	private static Displayable instance ;
	synchronized public static Displayable getInstance()
	{
		if(instance == null)
			instance = new HighScreen() ;
		return instance ;
	}
	private HighScreen()
	{
		super("高分排榜") ;
		//setType(AlertType.INFO) ;
		//setTimeout(Alert.FOREVER) ;
		append("\n\n\n第1名： 孔建军 100秒\n第2名： 卢文强 99秒\n第3名： 褚凌霞 90秒\n第4名： 李超 85秒\n第5名： 李忠 80秒\n第6名： 戴朝清 80秒\n第7名： 王艳丽 79秒\n第7名： 王鑫 62秒\n第8名： 郭灵芝 61秒\n");
		addCommand(new Command("返回",Command.BACK,1)) ;	
		setCommandListener(this) ;
	}
	public void commandAction(Command c,Displayable s)
	{
		Navigator.flow(c.getLabel()) ;
	}
}
