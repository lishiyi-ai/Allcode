<%--
  Created by IntelliJ IDEA.
  User: shiyi
  Date: 2023/3/1
  Time: 22:01
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>异步提交商品</title>
  <script type="text/javascript" src="${pageContext.request.contextPath}/js/jquery.min.js"></script>
</head>
<body>
<form id="products">
  <table style="border: 1px">
    <tr>
      <th>商品id</th><th>商品名称</th><th>提交</th>
    </tr>
    <tr>
      <td>
        <input name="proId" value="1" id="proId" type="text">
      </td>
      <td><input name="proName" value="三文鱼" id="proName" type="text"></td>
      <td><input type="button" value="提交单个商品" onclick="submitProduct()"></td>
    </tr>
    <tr>
      <td>
        <input name="proId" value="2" id="proId2" type="text">
      </td>
      <td><input name="proName" value="红牛" id="proName2" type="text"></td>
      <td><input type="button" value="提交多个商品" onclick="submitProducts()"></td>
    </tr>
  </table>
</form>
<script type="text/javascript">
  function submitProduct(){
    let Id = $("#proId").val();
    let Name =$("#proName").val();
    $.ajax({
      url:"${pageContext.request.contextPath}/getProduct",
      type:"post",
      data:JSON.stringify({proId:Id,proName:Name}),
      contentType:"application/json;charset=UTF-8",
      dateType:"json",
      success:function(response){alert(response);}
    });
  }
  function submitProducts(){
    let pro1 = {proId:$("#proId").val(),proName:$("#proName").val()}
    let pro2 ={proId:$("#proId2").val(),proName:$("#proName2").val()}
    $.ajax({
      url:"${pageContext.request.contextPath}/getProductList",
      type:"post",
      data:JSON.stringify([pro1,pro2]),
      contentType:"application/json;charset=UTF-8",
      dateStyle:"json",
      success:function(response){alert(response);}
    });
  }
</script>
</body>
</html>
