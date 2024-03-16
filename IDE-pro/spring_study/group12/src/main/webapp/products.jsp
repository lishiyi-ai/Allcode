<%--
  Created by IntelliJ IDEA.
  User: shiyi
  Date: 2023/3/1
  Time: 20:50
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>提交商品</title>
</head>
<body>
<%--向何处发王数据 action--%>
<form action="${pageContext.request.contextPath}/getProducts" method="post">
    <table style="width:220px;border:1cm">
        <tr><td>选择</td><td>商品名称标签</td></tr>
        <tr>
            <td>
                <input name="proIds" value="1" type="checkbox">
            </td>
            <td>java基础案例</td>
        </tr>
        <tr>
            <td>
                <input name="proIds" value="2" type="checkbox">
            </td>
            <td>javaWeb案例</td>
        </tr>
        <tr>
            <td>
                <input name="proIds" value="3" type="checkbox">
            </td>
            <td>SSM框架实战</td>
        </tr>
    </table>
    <input type="submit" value="提交商品"/>
</form>
</body>
</html>
