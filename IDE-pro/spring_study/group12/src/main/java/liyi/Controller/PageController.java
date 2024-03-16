package liyi.Controller;

import liyi.pojo.User;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.http.HttpServletRequest;

@Controller
public class PageController {
    @RequestMapping("/Pageregister")
    public void showPageByVoid(){
        System.out.println("showPageByVoid running");
    }

    @RequestMapping("/showPageByString")
    public String showPageByString(){
        System.out.println("showPageByString");
        return "forward:orders.jsp";
    }

    @RequestMapping("/showPageByForward")
    public String showPageByForward(){
        System.out.println("showPageByRedirect running");
        return "redirect:https://www.ithheima.com";
    }

    @RequestMapping("/showPageByRequest")
        public String showPageByRequest(HttpServletRequest request){
        System.out.println("showPageByRequest running");
        request.setAttribute("username","request");
        return "register1";
    }
    @RequestMapping("/showPageByModel")
        public String showPageByModel(Model model){
        System.out.println("showPageByModel running");
        model.addAttribute("username","model");
        User user=new User();
        user.setPassword("password");
        model.addAttribute("user",user);
        return "register1";
    }

    @RequestMapping("/showModelAndView")
    public ModelAndView showModelAndView(){
        ModelAndView modelAndView=new ModelAndView();
        modelAndView.addObject("username","heima");
        User user=new User();
        user.setPassword("password2");
        modelAndView.addObject("user",user);
        modelAndView.setViewName("register1");
        return modelAndView;
    }
}
