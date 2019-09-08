<%@ Page language="c#" Codebehind="WebForm1.aspx.cs" AutoEventWireup="True" Inherits="first.WebForm1" %>
<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.0 Transitional//EN" >
<HTML>
	<HEAD>
		<title>WebForm1</title>
		<meta name="GENERATOR" Content="Microsoft Visual Studio .NET 7.1">
		<meta name="CODE_LANGUAGE" Content="C#">
		<meta name="vs_defaultClientScript" content="JavaScript">
		<meta name="vs_targetSchema" content="http://schemas.microsoft.com/intellisense/ie5">
	</HEAD>
	<body MS_POSITIONING="GridLayout">
		<form id="Form1" method="post" runat="server">
			<asp:Label id="Label1" style="Z-INDEX: 101; LEFT: 184px; POSITION: absolute; TOP: 48px" runat="server"
				Width="96px" Font-Bold="True">统计结算单</asp:Label>
			<asp:Label id="Label2" style="Z-INDEX: 102; LEFT: 88px; POSITION: absolute; TOP: 96px" runat="server">饭钱</asp:Label>
			<asp:Label id="Label3" style="Z-INDEX: 103; LEFT: 88px; POSITION: absolute; TOP: 152px" runat="server">折扣</asp:Label>
			<asp:Label id="Label4" style="Z-INDEX: 104; LEFT: 88px; POSITION: absolute; TOP: 208px" runat="server">总计</asp:Label>
			<asp:TextBox id="TextBox1" style="Z-INDEX: 105; LEFT: 168px; POSITION: absolute; TOP: 88px" runat="server"></asp:TextBox>
			<asp:TextBox id="TextBox2" style="Z-INDEX: 106; LEFT: 168px; POSITION: absolute; TOP: 144px"
				runat="server"></asp:TextBox>
			<asp:TextBox id="TextBox3" style="Z-INDEX: 107; LEFT: 168px; POSITION: absolute; TOP: 200px"
				runat="server"></asp:TextBox>
			<asp:Button id="Button1" style="Z-INDEX: 108; LEFT: 176px; POSITION: absolute; TOP: 272px" runat="server"
				Width="80px" Text="提交" onclick="Button1_Click"></asp:Button>
		</form>
	</body>
</HTML>
