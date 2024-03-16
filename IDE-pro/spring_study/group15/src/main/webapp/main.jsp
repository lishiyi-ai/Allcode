<%--
  Created by IntelliJ IDEA.
  User: shiyi
  Date: 2023/3/9
  Time: 20:42
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<ul class="nav navbar-nav">
  <li class="dropdown user suer-menu">
    <a>
      <img src="${pageContext.request.contextPath}/img/user.jpg"
           class="user-image" alt="User Image">
      <span class="hidden-xs">${USER_SESSION.name}</span>
    </a>
  </li>
  <li class="dropdown user user-menu">
    <a href="${pageContext.request.contextPath}/logout">
      <span class="hidden-xs">注销</span>
    </a>
  </li>
</ul>
