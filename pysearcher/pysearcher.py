#!/usr/bin/env python
#encoding=utf-8
#Copyright @ 2008 Jianjun Kong
import wx
import sys 
import os,sys,string
import wx.richtext as rt

def find_it(x, lines):
    ret = []
    for line in lines:
	if line.find(x)!=-1:
		ret.append(line.split(":")[0].strip())
    return ret

def search(x = ''):
    if x == '':
	return
    global result
    result = []
    try: 
	f = open('pinyin.txt', 'r')
    finally:
	bytes = f.read()
	lines = bytes.split('\n')
	#lines = bytes.split('\r\n')
	#for c in x.decode('utf-8'):
	xchar = [' ', '\n', '\t']
	for c in x:
	    if c == u'-' or c in xchar:
		continue
	    if c in string.letters:
		continue
	    if c in string.digits:
		continue
	    ret = find_it(c.encode('utf-8'), lines)
	    if ret:
		result.append(c+':'+'/'.join(ret))
	f.close()
    return result

def proc_py(str,tone):

    if tone=='5':
        return str
    arry_a = ['ā', 'á', 'ǎ', 'à']
    arry_o = ['ō', 'ó', 'ǒ', 'ò']
    arry_e = ['ē', 'é', 'ě', 'è']
    arry_i = ['ī', 'í', 'ǐ', 'ì']
    arry_u = ['ū', 'ú', 'ǔ', 'ù']
    arry_v = ['ǖ', 'ǘ', 'ǚ', 'ǜ']
    #arry_A = ['Ā', 'Á', 'Ǎ', 'À']
    #arry_O = ['Ō', 'Ó', 'Ǒ', 'Ò']
    #arry_E = ['Ē', 'É', 'Ě', 'È']
    if 'iu' in str :
    	return string.replace(str,'u',arry_u[int(tone)-1],maxsplit=1)
    if 'ui' in str:
    	return string.replace(str,'i',arry_i[int(tone)-1],maxsplit=1)

    if 'a' in str:
    	return string.replace(str,'a',arry_a[int(tone)-1],maxsplit=1)
    if 'o' in str:
    	return string.replace(str,'o',arry_o[int(tone)-1],maxsplit=1)
    if 'e' in str:
    	return string.replace(str,'e',arry_e[int(tone)-1],maxsplit=1)
    if 'i' in str :
    	return string.replace(str,'i',arry_i[int(tone)-1],maxsplit=1)
    if 'u' in str:
    	return string.replace(str,'u',arry_u[int(tone)-1],maxsplit=1)
    if 'v' in str:
    	return string.replace(str,'v',arry_v[int(tone)-1],maxsplit=1)

    return str



class Panel(wx.Panel):
    def __init__(self, parent,id):
        wx.Panel.__init__(self, parent, id, style=wx.BORDER_SUNKEN)
        self.Bind(wx.EVT_RIGHT_DOWN, self.OnRightDown, self)
        sizer = wx.BoxSizer(wx.HORIZONTAL)
        gsleft = wx.BoxSizer(wx.VERTICAL)
	self.display=wx.TextCtrl(self, -1, '', style=wx.TE_MULTILINE)
	self.display.SetEditable(False)
	self.display.SetBackgroundColour('#fff')
        gsleft.Add(self.display, 4, wx.EXPAND |wx.TOP|wx.LEFT,5)

	self.printbycolor("#0D09BA", 'Display')
	self.printbycolor("#000", 'The ')
	self.printbycolor("#B63A00", 'Result ')
	self.printbycolor("#1C7717", 'Of ')
	self.printbycolor("#000", 'Search ')
	self.printbycolor('#B63A00', 'Here.....\n')

        self.inputtext = wx.TextCtrl(self, -1, 'Input or Paste Chinese Words...', style=wx.TE_MULTILINE)
	self.inputtext.AppendText('')
        gsleft.Add(self.inputtext, 1, wx.EXPAND | wx.TOP|wx.LEFT, 5)
	self.inputtext.SetFocus()
	self.inputtext.SetSelection(0, 31)
        gsright = wx.BoxSizer(wx.VERTICAL)
	otext=wx.StaticText(self, -1, '\n\t汉字\n魅环宇宙载风云\n力透万年尽国魂\n语润民风真善美\n文旋山海演红尘\n\nAuthor:\n  Jianjun Kong\n  (孔建军)\nkongove.cn', size=(100,180))
        otext.Bind(wx.EVT_RIGHT_DOWN, self.OnRightDown,otext)
	gsright.Add(otext, 0, wx.EXPAND)
	global texts
        texts = ['Clear', 'Paste', 'Search', 'Record', 'Quit']
        for t in texts:
            button = wx.Button(self, -1, t, style=wx.TE_LEFT)
            self.Bind(wx.EVT_BUTTON, self.OnClick, button)
            button.Bind(wx.EVT_RIGHT_DOWN, self.OnRightDown,button)
            gsright.Add(button, 9, wx.EXPAND)
	
        sizer.Add(gsleft, 40, wx.EXPAND | wx.RIGHT | wx.BOTTOM, 5)
        sizer.Add(gsright, 0.1, wx.EXPAND |wx.TOP|wx.BOTTOM|wx.RIGHT , 4)
        self.SetSizer(sizer)
    def OnRightDown(self, event):
        description = "This programme is used to search the right Pinyin of Chinese, which is input or pasted by user."
        licence = "GNU General Public License version 2"
        info = wx.AboutDialogInfo()
        info.SetVersion('1.0')
        info.SetName('Python Pinyin Seacher')
        info.SetCopyright('(C) 2008 Jianjun Kong')
        info.SetWebSite('http://kongove.cn')
        info.SetDescription(description)
        info.SetLicence(licence)
        info.AddDeveloper('Jianjun Kong(孔建军) kongjianjun@gmail.com\n程序基于Wangcong,Cocobear的相关代码在此表示感谢！')

        wx.AboutBox(info)

    def printbycolor(self, color, str):
	self.display.SetDefaultStyle(wx.TextAttr(color))
        self.display.WriteText(str)
    def click_b_paste(self, event):
	self.inputtext.SetValue("")
	self.inputtext.Paste()

    def click_b_clear(self, event):
        self.inputtext.SetValue("")
	self.display.SetValue('')

    def click_b_search(self, event):
	if  self.inputtext.GetValue()=='':
		return
	self.display.SetValue('')
	v = self.inputtext.GetValue()
	r = search(v)
	if r != []:
	    for i in r:
		self.printbycolor("#0D09BA", '"'+i.split(":")[0].strip()+'"')
		self.printbycolor("#000", ' can be read as : ')
		str = i.split(":")[1].strip()
		str = str.split("/")
		num = 0
		for j in str:
		    str2 = j
		    str3 = []
		    for k in str2.encode('ascii'):
			str3.append(k)

		    tone=string.join(str3[-1:],'')
		    self.printbycolor("#B63A00", proc_py(string.join(str3[:-1],''),tone))
		    if num < len(str)-1:
	 	        self.printbycolor("#1C7717", ' / ')
		    num += 1
		self.display.WriteText('\n')

    def click_b_record(self, event):
	str=self.display.GetValue() 
	record_f=open("record_pinyin.txt",'a')
	for i in string.join(str,'').encode('utf-8').split('\n'):
		if 'can be read as' in i:
			record_f.write(i+'\n')
	record_f.close()
	self.printbycolor("#0D09BA","\nIt has been recorded to ")
	self.printbycolor("#B63A00","record_pinyin.txt\n")

    def OnClick(self, event):
        label = event.EventObject.GetLabel()
        nums = range(10)
        nums.append('.')
	#self.display.SetValue('')
        for s in texts: 
	    if label == 'Quit':
	        sys.exit()
            if label == s:
                {'Paste':self.click_b_paste,
                'Clear':self.click_b_clear,
		'Search':self.click_b_search,
		'Record':self.click_b_record}[s](event)

class Cal(wx.Frame):
    def __init__(self, parent, id, title):
        wx.Frame.__init__(self, parent, id, title, size=(480,350))
        panel = Panel(self,-1)
        hbox = wx.BoxSizer()
        hbox.Add(panel, -1, wx.EXPAND)

        self.SetSizer(hbox)
        self.Centre()
        self.Show(True)
def main():
    app = wx.App()
    Cal(None,-1, 'Python Pinyin Seacher')
    app.MainLoop()

if __name__ == "__main__":
    sys.exit(main())
