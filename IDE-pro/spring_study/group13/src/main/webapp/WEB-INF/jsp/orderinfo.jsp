<%--
  Created by IntelliJ IDEA.
  User: shiyi
  Date: 2023/3/2
  Time: 23:18
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>订单信息</title>
</head>
<body>
你好:${USER_SESSION.username}
<a href="${pageContext.request.contextPath}/logout">退出</a>
  <table width="220px" border="1">
    <tr align="center"><td colspan="2">订单id:D001</td></tr>
    <tr align="center"><td>商品名称</td></tr>
    <tr align="center"><td>三文鱼</td></tr>
    <tr align="center"><td>红牛</td></tr>
  </table>
</body>
</html>
