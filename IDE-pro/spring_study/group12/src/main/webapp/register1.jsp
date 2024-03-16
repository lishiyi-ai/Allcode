<%--
  Created by IntelliJ IDEA.
  User: shiyi
  Date: 2023/3/1
  Time: 16:56
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
  <meta http-equiv="Content-Type" content="text/html" charset="UTF-8">  <!--什么意思?-->
  <title>注册</title>
</head>
<body>
<form action="${pageContext.request.contextPath}/registerUser">
  用户名:<input type="text" name="username" value="${username}"/><br />
  密&nbsp;&nbsp;&nbsp;码:<input type="password" name="password" value="${user.password}"/><br />
  <input type="submit" value="注册"/>
</form>
</body>
</html>
