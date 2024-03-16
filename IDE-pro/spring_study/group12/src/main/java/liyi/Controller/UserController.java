package liyi.Controller;

import liyi.pojo.User;
import org.springframework.format.annotation.DateTimeFormat;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

import javax.servlet.http.HttpServletRequest;
import java.util.Date;

@Controller
public class UserController {
    @RequestMapping("/getUserId")
    public void getUserId(HttpServletRequest request){
        String userid= request.getParameter("userid");
        System.out.println("userid="+userid);
    }
    @RequestMapping("/getUserNameAndId")
    public void getUserNameAndId(String username,Integer userid){
        System.out.println("username="+username+",userid="+userid);
    }
    @RequestMapping("/getUserName")
    public void getUserName(@RequestParam(value = "name",
            required = false,defaultValue = "liyi") String username){
        System.out.println("username="+username);
    }
//    映射方式是REST风格时
    @RequestMapping("/user/{name}")
    public void getPathVariable(@PathVariable(value="name") String username){
        System.out.println("username="+username);
    }
    @RequestMapping("registerUser")
    public void registerUser(User user){
        String username=user.getUsername();
        String password=user.getPassword();
        System.out.println("username="+username+" password="+password);
    }
    @RequestMapping("/register")
    public String register(){
        return "register";
    }

    @RequestMapping("getBirthday")
    public void getBirthday(Date birthday){
        System.out.println("birthday="+birthday);
    }

    @RequestMapping("getBirthday1")
    public void getBirthday1(@DateTimeFormat(pattern = "yyyy-MM-dd") Date birthday){
        System.out.println("birthday="+birthday);
    }

    @RequestMapping("/findOrderWithUser")
    public void findOrderWithUser(User user){
        String username=user.getUsername();
        String orderId=user.getOrder().getOrderId();
        System.out.println("username="+username+"orderId="+orderId);
    }
}
