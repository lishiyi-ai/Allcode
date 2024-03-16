<%--
  Created by IntelliJ IDEA.
  User: shiyi
  Date: 2023/3/1
  Time: 23:33
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>商品添加</title>
    <script type="text/javascript" src="${pageContext.request.contextPath}/js/jquery.min.js"></script>
</head>
<body>
    <table id="products" border="1" width="60%">
        <tr align="center"><td>欢迎您:</td><td id="username"></td></tr>
        <tr align="center">
            <td colspan="2" align="center">
                <input type="button" value="添加多个商品" onclick="addProducts()">
            </td>
        </tr>
        <tr align="center"><td>商品id</td><td>商品名称</td></tr>
    </table>
<script type="text/javascript">
    window.onload=function(){
        var url="${pageContext.request.contextPath}/getUser";

        $.get(url,function(response){
            $("#username").text(response.username);
        })
    }
    function addProducts(){
        var url="${pageContext.request.contextPath}/addProducts";
        $.get(url,function (products){
            for(var i=0;i<products.length;i++){
                $("#products").append("<tr><td>"+products[i].proId+"</td>" +
                    "<td>"+products[i].proName+"</td></tr>")
            }
        })
        <%--$.ajax({--%>
        <%--    url:"${pageContext.request.contextPath}/addProducts",--%>
        <%--    type:"post",--%>
        <%--    data:JSON.stringify(["你好","你好"]),--%>
        <%--    contentType:"application/json;charset=UTF-8",--%>
        <%--    dateStyle:"json",--%>
        <%--    success:function(response){alert(response);},--%>
        <%--    error:function (){--%>
        <%--        alert("网络异常");--%>
        <%--    }--%>
        <%--});--%>
    }
</script>
</body>
</html>
