<%--
  Created by IntelliJ IDEA.
  User: shiyi
  Date: 2023/3/2
  Time: 23:15
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>用户登录</title>
</head>
<body>
    <form action="${pageContext.request.contextPath}/login" method="POST">
        <div>${msg}</div>
        用户名：<input type="text" name="username"/><br/>
        密&nbsp;&nbsp;码:
        <input type="text" name="password"/><br/>
        <input type="submit" value="登录"/>
    </form>
</body>
</html>
