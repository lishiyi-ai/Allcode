package liyi.Controller;

import com.fasterxml.jackson.databind.ObjectMapper;
import liyi.pojo.Product;
import liyi.pojo.User;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

@Controller
public class DataController {
    @RequestMapping("showDataByResponse")
    public void showDataByResponse(HttpServletResponse response){
        try{
            response.getWriter().print("response");
        }catch(IOException e){
            e.printStackTrace();
        }
    }

    //    对象数据转换成Json
    @RequestMapping("showDataByJSON")
    public void showDataByJSON(HttpServletResponse response){
        try{
            ObjectMapper om=new ObjectMapper();
            User user=new User();
            user.setUsername("heima");
            user.setUsername("6666");
//            将数据转化为json
            String ujson=om.writeValueAsString(user);
            response.getWriter().print(ujson);
        }catch(IOException e){
            e.printStackTrace();
        }
    }

//    集合数据转换成Json
    @RequestMapping("getUser")
    @ResponseBody
    public User getUser(){
        User user=new User();
        user.setUsername("heima3");
        return user;
    }

    @RequestMapping("addProducts")
    @ResponseBody
    public List<Product> addProducts(){
        Product p1=new Product();
        p1.setProId("p001");
        p1.setProName("红牛");
        Product p2=new Product();
        p2.setProId("p002");
        p2.setProName("三文鱼");
        ArrayList<Product> products=new ArrayList<>();
        products.add(p1);
        products.add(p2);
        return products;
    }
}
