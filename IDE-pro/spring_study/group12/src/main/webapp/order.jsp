<%--
  Created by IntelliJ IDEA.
  User: shiyi
  Date: 2023/3/1
  Time: 21:21
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <meta http-equiv="Content-Type" content="text/html"; charset="UTF-8">
    <title>订单</title>
</head>
<body>
    <form action="${pageContext.request.contextPath}/findOrderWithUser" method="post">
        所属用户:<input type="text" name="username"/><br />
        订单编号:<input type="text" name="order.orderId"><br />
        <input type="submit" value="查询" />
    </form>
</body>
</html>
