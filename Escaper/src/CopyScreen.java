import javax.microedition.lcdui.* ;
public class CopyScreen extends Alert
{
	private static Displayable instance ;
	synchronized public static Displayable getInstance()
	{
		if(instance == null)
			instance = new CopyScreen() ;
		return instance ;
	}
	private CopyScreen()
	{
		super("游戏说明") ;
		setString("使用方向键控制飞机移动，躲避子弹，碰到子弹时游戏结束。\n\n\n" +
				"版本号V1.0\n版权所有 (C) 西邮 2008") ;
		setType(AlertType.INFO) ;
		setTimeout(Alert.FOREVER) ;
	}
}
