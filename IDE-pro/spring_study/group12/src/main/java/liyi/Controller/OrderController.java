package liyi.Controller;

import liyi.pojo.Order;
import liyi.pojo.Product;
import liyi.pojo.User;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

import java.util.HashMap;
import java.util.List;
import java.util.Set;

@Controller
public class OrderController {
    /**
     * 获取用户中的订单信息
     */
//    属性为List的数据绑定
    @RequestMapping("showOrders")
    public void showOrders(User user){
        List<Order> orders=user.getOrders();
        List<String> addressList=user.getAddress();
        System.out.println("di：订单");
        for(int i=0;i<orders.size();i++){
            Order order=orders.get(i);
            String address=addressList.get(i);
            System.out.println("订单Id:"+order.getOrderId());
            System.out.println("订单配送地址:"+address);
        }
    }

//    属性为Map类型的数据绑定
    @RequestMapping("orderInfo")
    public void getOrderInfo(Order order){
        String orderId=order.getOrderId();
        HashMap<String, Product> orderInfo=order.getProductInfo();
        Set<String> keys=orderInfo.keySet();
        System.out.println("订单id:"+orderId);
        System.out.println("订单商品信息:");
        for(String key:keys){
            Product product=orderInfo.get(key);
            String proId=product.getProId();
            String proName=product.getProName();
            System.out.println(key+"类~"+"商品id:"+proId+" 商品名称:"+proName);
        }
    }
}
