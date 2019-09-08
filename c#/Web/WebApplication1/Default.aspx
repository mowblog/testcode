<%@ Page Language="C#" AutoEventWireup="true" CodeBehind="Default.aspx.cs" Inherits="WebApplication1._Default" %>

<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">

<html xmlns="http://www.w3.org/1999/xhtml">
<head runat="server">
    <title></title>
   <!-- <meta http-equiv="Refresh" content="10"/> -->
</head>
<body>
    <form id="form1" runat="server">
    <div>
         
         <asp:TextBox id="login_TextBox" style="Z-INDEX: 105; LEFT: 90px; POSITION: absolute; TOP: 35px" runat="server" Width="240px" Height="100px" Wrap="true" TextMode="MultiLine"></asp:TextBox>  

         <asp:Button id="login_Button" style="Z-INDEX: 108; LEFT: 8px; POSITION: absolute; TOP: 35px" runat="server" Width="80px" Text="hasp.Login" onclick="Button1_Click"></asp:Button>

         <asp:TextBox id="logout_TextBox" style="Z-INDEX: 105; LEFT: 90px; POSITION: absolute; TOP: 150px" runat="server" Width="240px"></asp:TextBox>  

         <asp:Button id="logout_Button" style="Z-INDEX: 108; LEFT: 8px; POSITION: absolute; TOP: 150px" runat="server" Width="80px" Text="hasp.Logout" onclick="Button2_Click"></asp:Button>

    </div>
    </form>
</body>
</html>

