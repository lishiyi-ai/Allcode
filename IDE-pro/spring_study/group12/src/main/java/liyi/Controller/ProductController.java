package liyi.Controller;

import liyi.pojo.Product;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;

import java.util.List;

@Controller
public class ProductController {
    /**
     * 获取商品列表
     */
//    数组绑定
    @RequestMapping("/getProducts")
    public void getProducts(String[] proIds){
        System.out.println(proIds);
        for(String proId:proIds){
            System.out.println("获取到了Id为"+proId+"的商品");
        }
    }
//    集合绑定
    @RequestMapping("/getProducts1")
    public void getProducts(@RequestParam("proIds") List<String> proIds){
        for(String proId:proIds){
            System.out.println("获取到了Id为"+proId+"的商品");
        }
    }

//    @RequestBody 注解结合Jackson提供的json格式转换器
    @RequestMapping("/getProduct")
    public void getProduct(@RequestBody Product product){
        String proId=product.getProId();
        String proName=product.getProName();
        System.out.println("获得到了Id为"+proId+"名称为"+proName+"的商品");
    }

    @RequestMapping("/getProductList")
    public void getProductList(@RequestBody List<Product> products){
        for(Product product:products){
            String proId=product.getProId();
            String proName=product.getProName();
            System.out.println("获取到Id为"+proId+"名称为"+proName+"的商品");
        }
    }
}
