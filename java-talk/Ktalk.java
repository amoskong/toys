/*
 * Filename: Ktalk.java
 * Author: Jianjun Kong
 * CopyRight @ kongove.cn
 * Data: June 25,2008
 * License GPLv3
*/

import java.io.*;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.Date;
import java.text.DateFormat;
import java.text.Format;
import java.text.SimpleDateFormat;
import java.net.*;

public class Ktalk
{
    public static class kSocket // 数据通信类，专门用公用Socket收发数据
    {
        DatagramSocket dSocket;
        DatagramPacket inPacket;
        DatagramPacket outPacket;
        InetAddress Addr;

        byte[] inBuffer = new byte[100];
        byte[] outBuffer;
        String str = "";

        kSocket()
        {
            try{
                dSocket = new DatagramSocket(1986);     // socket 端口1986
                Addr = InetAddress.getByName(local);
            }
            catch (IOException e){
                System.out.println("IOException occurred with socket.");
                System.out.println(e);
                e.printStackTrace();
            }
        }

        void sendMsg(String ss,InetAddress addr)        // 发送数据
        {
            System.out.println("Send message :"+addr.toString()+" :"+ss);

            try{
                outBuffer = ss.getBytes();
                outPacket = new DatagramPacket(outBuffer, outBuffer.length, addr, 1986  );  //把数据写入socket
                dSocket.send(outPacket);
            }
            catch (IOException e){
                System.out.println("IOException occurred with socket.");
                System.out.println(e);
                e.printStackTrace();
            }
        }
        String receiveMsg()     // 接受数据
        {
            System.out.println("Receive message......");

             try{
                inPacket = new DatagramPacket(inBuffer, inBuffer.length);
                dSocket.receive(inPacket);      // 从socket读取数据
                Addr = inPacket.getAddress();
                str = new String(inPacket.getData(), 0, inPacket.getLength());
                System.out.println("Receive message: "+Addr+" : " + str);

            }
            catch (IOException e){
                System.out.println("IOException occurred with socket.");
                System.out.println(e);
                e.printStackTrace();
            }
            return str;
       }

    }

    private static kSocket s;
    public static String local="192.168.1.12";
    public static int []flag;   //标记用户子窗口是否新建，0为未新建，1为已新建

    public static class subWindow //extends Frame   //子窗口类
    {

        private JTextArea outText;
        private  JTextArea inText;
        private  JTextField nameText;
        private  JTextField autoText;
        public InetAddress addr;
        private JFrame app;
        public JCheckBox huifuRB;
        public Boolean fb;
        private int N;

        subWindow(String ss,String name,int i)  //初始化子窗口类
        {
            try{

                addr=InetAddress.getByName(local);
            }
            catch(IOException e){
                System.out.println("IOException occurred with socket.");
                System.out.println(e);
                e.printStackTrace();
            }

            int port=1986;
            fb=false;
            N=i;

            app=new JFrame("SubWindow:["+name+"]Talks With["+ss+"]");
            Container container=app.getContentPane();
            container.setLayout(new FlowLayout());
            outText=new JTextArea("",20,57);
            inText=new JTextArea("",7,57);

            JTextField idText=new JTextField("用户名:",4);
            idText.setEditable(false);
            nameText=new JTextField(name,5);
            JButton blodButton=new JButton("B");
            JButton iButton=new JButton("I");
            huifuRB=new JCheckBox("自动回复");
            autoText=new JTextField("我有事，过会联系！",25);
            JButton sendButton=new JButton("发送");
            JButton closeButton=new JButton("关闭");

            container.add(new JScrollPane(outText));

            container.add(blodButton);
            container.add(iButton);
            container.add(huifuRB);
            container.add(autoText);
            container.add(new JScrollPane(inText));
            container.add(sendButton);
            container.add(closeButton);
            //container.add(new JScrollPane(b));
            outText.setEditable(false);
            app.setSize(650,600);
            app.setVisible(true);
            app.setResizable(false);
            //app.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

            huifuRB.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
                    if(fb)
                        fb=false;
                    else
                        fb=true;
                }
            });

            closeButton.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
                    flag[N]=0;
                    app.setVisible(false);
                }
            });
            sendButton.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
                    Date d=new Date();
                    String str=new String();
                    Format format = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");

                    str=format.format(d)+" "+nameText.getText()+" :\n"+inText.getText()+"\n";
                    outText.append(str);
                    inText.setText("");
                    s.sendMsg(str,s.Addr);
                }
            });
        }
        public void print(String str)   //输出信息到聊天窗口文本区
        {
            outText.append(str);

        }
    }

    public static class mainWindow extends Frame  //主窗口类
    {
        int max=10;     //设置最大用户数量
        int i=0;
        int j=0;

        public subWindow []sub;
        private static JButton []user;
        private JTextField nameText;
        public static InetAddress []addr;
        //public static int []flag;
        Container container;

        mainWindow()    //初始化主窗口类
        {
            s=new kSocket();
            sub=new subWindow[max];
            user=new JButton[max];
            addr=new InetAddress[max];
            flag=new int[max];
            JTextField statusText;
            JFrame app=new JFrame("mainWindow");
            container=app.getContentPane();
            container.setLayout(new FlowLayout());
            //JButton idButton=new JButton("上线");
            JTextField idText=new JTextField("昵称:",3);
            idText.setEditable(false);
            nameText=new JTextField("匿名用户",8);
            //container.add(idButton);
            container.add(idText);
            container.add(nameText);
            //JTextArea Text=new JTextArea("",30,16);

            nameText.addActionListener(new java.awt.event.ActionListener() {
                public void actionPerformed(java.awt.event.ActionEvent evt) {
                    try{
                        s.sendMsg("//login:"+nameText.getText(),InetAddress.getByName("192.168.1.255"));
                        // 用数据通信类广播上线信息
                    }
                    catch (IOException e){
                         System.out.println("IOException occurred with socket.");
                         System.out.println(e);
                         e.printStackTrace();
                    }
                }
            });

            for(i=0;i<max;i++)  // 初始化数据结构
            {
                flag[i]=0;
                user[i]=new JButton("空闲信道");
                user[i].setEnabled(false);

                try{
                    addr[i]=InetAddress.getByName("");
                }
                catch (IOException e){
                    System.out.println("IOException occurred with socket.");
                    System.out.println(e);
                    e.printStackTrace();
                }

                container.add(user[i]);
                user[i].setSize(200,300);
            }

                //为按钮添加创建子窗口类的监听事件
                user[0].addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        makeSub(0);
                    }
                });
                user[1].addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        makeSub(1);
                    }
                });
                user[2].addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        makeSub(2);
                    }
                });
                user[3].addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        makeSub(3);
                    }
                });
                user[4].addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        makeSub(4);
                    }
                });
                user[5].addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        makeSub(5);
                    }
                });
                user[6].addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        makeSub(6);
                    }
                });
                user[7].addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        makeSub(7);
                    }
                });
                user[8].addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        makeSub(8);
                    }
                });
                user[9].addActionListener(new ActionListener()
                {
                    public void actionPerformed(ActionEvent event)
                    {
                        makeSub(9);
                    }
                });

            statusText=new JTextField("CopyRight @ 孔建军",12);
            statusText.setEditable(false);
            JButton loginB=new JButton("上线");
            JButton exitB=new JButton("退出");
            app.add(statusText);
            app.add(loginB);
            app.add(exitB);

            // 为上线按钮添加监听事件
            loginB.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
                    try{
                        s.sendMsg("//login:"+nameText.getText(),InetAddress.getByName("192.168.1.255"));
                        // 广播上线提示信息
                    }
                    catch (IOException e){
                        System.out.println("IOException occurred with socket.");
                        System.out.println(e);
                        e.printStackTrace();
                    }
                }
            });
            exitB.addActionListener(new ActionListener()
            {
                public void actionPerformed(ActionEvent event)
                {
                    try{
                        s.sendMsg("//exit:",InetAddress.getByName("192.168.1.255"));
                        // 用数据通信类发送下线信息
                        //s.dSocket.close();
                    }
                    catch (IOException e){
                        System.out.println("IOException occurred with socket.");
                        System.out.println(e);
                        e.printStackTrace();
                    }
                    System.exit(0);
                }
            });

            app.setSize(150,445);
            app.setVisible(true);
            app.setResizable(false);
            app.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

            last();         // 程序最终流程运行到此，进入while循环接收数据
        }
        public void makeSub(int i)  //创建子窗口类
        {
            if(flag[i]==0)
            {
                sub[i]=new subWindow(user[i].getLabel(),nameText.getText(),i);
                flag[i]=1;
            }
        }
         public void last()
         {
           Boolean f;
          while(true)       // 进入while循环接收数据
            {
                f=false;
                String str=s.receiveMsg();      // 用数据通信类接收数据


                if(str.startsWith("//exit"))    // 用户下线处理
                {
                        for(i=0;i<=j;i++)
                        {
                            System.out.println("hhhhh:  addr[i]: +"+addr[i]+"s.Addr: "+s.Addr+" : "+i);
                            if(addr[i].equals(s.Addr))
                            {
                                System.out.println("addr[i]等于s.Addr  "+i+"  "+j);

                                for(int p=i;p<j-1;p++)
                                {
                                    user[p].setLabel(user[p+1].getLabel());
                                    addr[p]=addr[p+1];
                                }
                                user[j-1].setText("空闲信道");
                                user[j-1].setEnabled(false);
                                try{
                                    addr[j-1]=InetAddress.getByName(local);
                                }
                                catch(IOException e){
                                    System.out.println("IOException occurred with socket.");
                                    System.out.println(e);
                                    e.printStackTrace();
                                }
                                j--;
                                f=true;
                                break;
                            }
                        }
                        if(f)
                        {
                            continue;
                        }
                }


                if(str.startsWith("//login") && j<max)  // 用户上线处理，添加按钮、更新按钮
                {

                    try{
                        System.out.println("s.Addr:"+s.Addr+" :  ");

                        for(i=0;i<=j;i++)
                        {
                            System.out.println("hhhhh:  addr[i]: +"+addr[i]+"s.Addr: "+s.Addr+" : "+i);
                            if(addr[i].equals(s.Addr))
                            {
                                System.out.println("addr[i]等于s.Addr");
                                f=true;
                                break;
                            }
                        }
                        if(f)
                        {
                            user[i].setLabel(str.split(":")[1]);
                            continue;
                        }

                        if(s.Addr.equals(InetAddress.getByName(local)));
                        {
                            System.out.println("接收到Localhost发来数据");
                            //if(false)
                            //break;
                        }

                        user[j].setLabel(str.split(":")[1]);
                        user[j].setEnabled(true);
                    }
                    catch (IOException e){
                        System.out.println("IOException occurred with socket.");
                        System.out.println(e);
                        e.printStackTrace();
                    }
                    if(j>0 && !str.startsWith("//login_reply"))
                    {
                        s.sendMsg("//login_reply:"+nameText.getText(),s.Addr);  // 对首次发送上线提示的主机，回应信息
                        System.out.println("send //login_reply to"+s.Addr);
                    }

                    addr[j++]=s.Addr;   // 将数据通信ip地址，存储在对应的数组元素里
                }
                for(int i=0;i<j;i++)
                {

                    if(flag[i]==1)      // 子窗口已经创建
                    {

                        System.out.println(addr[i]+"||"+s.Addr);
                        if(addr[i].equals(s.Addr))  //找到地址对应的子窗口，并显示信息
                        {
                            sub[i].print(str);

                            if(sub[i].fb)
                            {
                                Date d=new Date();
                                String str2=new String();
                                Format format = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                                str2=format.format(d)+" "+nameText.getText()+" :\n"+"自动回复:"+sub[i].autoText.getText()+"\n";
                                sub[i].outText.append(str2);
                                s.sendMsg(str2,s.Addr);
                            }
                        }
                    }
                    else
                    {
                        if(addr[i].equals(s.Addr) && !str.startsWith("//login") && !str.startsWith("//exit"))
                        // 找到地址对应的子窗口，str不为上线、下线提示信息
                        {
                            makeSub(i);
                            sub[i].print(str);
                            if(sub[i].fb)
                            {
                                Date d=new Date();
                                String str2=new String();
                                Format format = new SimpleDateFormat("yyyy-MM-dd hh:mm:ss");
                                str2=format.format(d)+" "+nameText.getText()+" :\n"+"自动回复:"+sub[i].autoText.getText()+"\n";
                                sub[i].outText.append(str2);
                                s.sendMsg(str2,s.Addr);
                            }
                        }
                    }
                }

                for(int k=0;k<max;k++)
                {
                    System.out.println("flag["+k+"]:"+flag[k]);
                    System.out.println("addr["+k+"]:"+addr[k]);
                }

            }
        }
    }

    public static void main(String args[])  //main函数类
    {
        mainWindow main=new mainWindow();   //创建主窗口类
    }

}
