#include <cstdio>
#include <map>
#include <stdlib.h>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <mysql/mysql.h>
using namespace std;
class Cart
{
    public:
    string GoodsName;//商品名
    string Class;//分类
    string  price;//单价
    string count;//数量
};
class Stack
{
    public:
    string GoodsName;//商品名
    string Class;//分类
    string  price;//单价
    string stack;//库存
};
class Classification
{
public:
    string class_id;
    string name;
    string pid;
};
class Goods
{
public:
    string goods_id;
    string name;
    string price;
    string stack;
    string description;
    string image;
    string place;
    string class_id;
};

class Menu
{
public:
    vector<Menu>*menu;
    string class_id;
    string name;
    string url;
    vector<Goods>* goods;
    Menu(){
        menu = NULL;
        goods = NULL;
    }
};
class User
{
public:
    string name;
    string account;
    string user_id;
    string phone;
    string address;
    string password;
    vector<Menu>* GetMenuList();//菜单列表
    Menu GetGoodsList(string classID,int n);//classID下面子分类和商品列表
    Goods GetGoodsInfo(string GoodsI_id);//返回某一具体商品信息
    vector<Goods>* SearchGoods(string searchstr,int n);//商品搜索,n是显示第n页
    User GetInfo();//获取个人信息
    bool ChangeInfo(User user);//更改个人信息
};
bool User::ChangeInfo(User user)
{
 MYSQL mysql;
    MYSQL_ROW row;
    MYSQL_RES *res;
    mysql_init(&mysql);
    mysql_real_connect(&mysql,"localhost","root","password","Supermarket",0,NULL,0);
   string sql ="select * from user where user_id=";
   sql = sql +"\'" + user.user_id + "\'";
   mysql_query(&mysql,sql.c_str());
   res = mysql_use_result(&mysql);
   if(res == 0)return 0;
   mysql_free_result(res);
   sql = "update user set ";
   sql = sql + "user_id="+ "\'" +user.user_id+"\',"+"account=" +"\'"+ user.account+"\'," + "password="+"\'" + user.password+"\',";
   if(user.name != "")
   {
       sql = sql + "name=" + "\'" +user.name+"\'";
   }else sql = sql + "name=\'NULL\'";
   sql += ",";
    if(user.phone!="")
   {
       sql = sql + "phone=" + "\'" +user.phone+"\'";
   }else sql = sql + "phone=\'NULL\'";
   sql += ",";
 
    if(user.address!="")
   {
       sql = sql + "address=" + "\'" +user.address+"\'";
   }else sql = sql + "address=\'NULL\'";

    sql = sql + " where user_id="+"\'"+user.user_id+"\'";
   mysql_query(&mysql,sql.c_str()); 
 mysql_close(&mysql);
    mysql_free_result(res);
   mysql_close(&mysql);
  return true; 
}
User User::GetInfo()
{
   User rec;
   MYSQL mysql;
    MYSQL_ROW row;
    MYSQL_RES *res;
    mysql_init(&mysql);
    mysql_real_connect(&mysql,"localhost","root","password","Supermarket",0,NULL,0);
   string sql = "select * from user where user_id= "; 
   sql = sql + "\'" + user_id + "\'";
   mysql_query(&mysql,sql.c_str());
   res = mysql_use_result(&mysql);
   if(res)
   {
       for(int i = 0;i < mysql_field_count(&mysql);i ++)
       {
           row = mysql_fetch_row(res);
           if(row == 0)break;
           rec.user_id = row[0];
           rec.account = row[1];
           rec.password = row[2];
           rec.name = row[3]?row[3]:"NULL";
           rec.phone = row[4]?row[4]:"NULL";
           rec.address = row[5]?row[5]:"NULL";
       }
   }
   mysql_free_result(res);
   mysql_close(&mysql);
   return rec;
}
Goods User::GetGoodsInfo(string goodid)
{
     MYSQL mysql;
    MYSQL_ROW row;
    MYSQL_RES *res;
    mysql_init(&mysql);
    mysql_real_connect(&mysql,"localhost","root","password","Supermarket",0,NULL,0);
   string sql = "select * from goods where goods_id =";
   sql = sql + "\'" +goodid+"\'"; 
   mysql_query(&mysql,sql.c_str());
   res = mysql_use_result(&mysql);
   Goods rec;
   if(res)
   {
       for(int i = 0;i < mysql_field_count(&mysql);i ++)
       {
         row = mysql_fetch_row(res);
         if(row == 0)break;
         rec.goods_id = row[0];
        rec.price = row[1];
        rec.stack = row[2];
        rec.place = row[3]?row[3]:"NULL";
        rec.image = row[4]?row[4]:"NULL";
        rec.description = row[5]?row[5]:"NULL";
        rec.class_id = row[6];
        rec.name = row[7];
       }
   }
   mysql_free_result(res);
   mysql_close(&mysql);
   return rec;
}
Menu User::GetGoodsList(string classid,int n)
{
    Menu men;
  MYSQL mysql;
    MYSQL_ROW row;
    MYSQL_RES *res;
    mysql_init(&mysql);
    mysql_real_connect(&mysql,"localhost","root","password","Supermarket",0,NULL,0);
  string sql = "select * from goods where class_id= ";
  sql = sql + "\'" + classid+"\'";
  //获取货物页数
   string l = "",r = "";
   char recordChar[33];
   int len = 0,start = (n-1)*10;
   while(start)
   {
      recordChar[len++] = start%10 + '0';
      start/=10;
   }
   if(len == 0)
       l = "0";
   for(int i = len-1;i >= 0;i--)
       l += recordChar[i];
   start = (n-1)*10 + 10 - 1;
   len = 0;
   while(start)
   {
       recordChar[len++] = start%10 + '0';
       start/=10;
   }
   for(int i = len - 1;i >= 0;i--)
       r += recordChar[i];
  sql = sql + string(" limit ")+ l+","+r;
  mysql_query(&mysql,sql.c_str());
  res = mysql_use_result(&mysql);
  men.goods = new vector<Goods>();
  Goods rec;
  if(res)
  {
    for(int i = 0;i < mysql_field_count(&mysql);i ++)
    {
        row = mysql_fetch_row(res);
        if(row == 0)break;
        rec.goods_id = row[0];
        rec.price = row[1];
        rec.stack = row[2];
        rec.place = row[3]?row[3]:"NULL";
        rec.image = row[4]?row[4]:"NULL";
        rec.description = row[5]?row[5]:"NULL";
        rec.class_id = row[6];
        rec.name = row[7];
        men.goods->push_back(rec);
    }
  }
  sql = "select name from classification where class_id =";
  sql = sql + "\'" + classid+"\'";
  mysql_query(&mysql,sql.c_str());
  res = mysql_use_result(&mysql);
  row = mysql_fetch_row(res);
  men.name = string(row[0]);
 mysql_free_result(res); 
  mysql_close(&mysql);

  return men;

}
vector<Menu>* User::GetMenuList()
{
    vector<Menu>* ret  = new vector<Menu>();
    vector<Menu> &tmp = *ret;
    MYSQL mysql;
    MYSQL mysql2;
    MYSQL_ROW row;
    MYSQL_RES *res=NULL;
    mysql_init(&mysql);
    mysql_init(&mysql2);
  mysql_real_connect(&mysql2,"localhost","root","password","Supermarket",0,NULL,0);
   mysql_real_connect(&mysql,"localhost","root","password","Supermarket",0,NULL,0);
    string sql1 = "select * from classification";
    mysql_query(&mysql,sql1.c_str());
    res = mysql_use_result(&mysql);
    Menu men;
    if(res)
    {
        for(int i = 0;i < mysql_field_count(&mysql);i ++)
        {
            row = mysql_fetch_row(res);
            if(row == 0)break;
            string classid(row[0]);
            string sql2 = "select name from goods where goods.class_id =";
            sql2 = sql2 +"\'" + classid + "\'";
            mysql_query(&mysql2,sql2.c_str());
            MYSQL_ROW row2;
            MYSQL_RES *res2;
            res2 = mysql_use_result(&mysql2);
            if(res2)
            {
                for(int j = 0;j < mysql_field_count(&mysql2);j ++)
                {
                    row2 = mysql_fetch_row(res2);
                    if(row2 == 0)break;
                    men.goods=SearchGoods(string(row2[0]),1);
                    men.class_id = classid;
                    men.name = row[1];
                    if(row[2] == NULL)
                        men.url = "";
                    else men.url = row[2];
                }
            }
            mysql_free_result(res2);
            tmp.push_back(men);
        }
    }
      for(int i = 0;i < tmp.size();i ++)
        for(int j = i + 1;j < tmp.size();j ++)
        {
            if(tmp[i].url == tmp[j].class_id)
            {
                if(tmp[j].menu == NULL)
                    tmp[j].menu = new vector<Menu>();
                (*tmp[j].menu).push_back(tmp[i]);
            }else if(tmp[j].url == tmp[i].class_id)
            {
                if(tmp[i].menu == NULL)
                    tmp[i].menu = new vector<Menu>();
                (*tmp[i].menu).push_back(tmp[j]);
            }
        }
    mysql_free_result(res);
    mysql_close(&mysql2);
    mysql_close(&mysql);
    return ret; 
}
vector<Goods> *User::SearchGoods(string searchstr,int n)
{
   vector<Goods>* p = new vector<Goods>(); 
   MYSQL mysql;
   MYSQL_ROW row;
   MYSQL_RES *res;
   mysql_init(&mysql);
   int start = (n-1)*10;
   //获得开头结尾的页数
   string l = "",r = "";
   char recordChar[33];
   int len = 0;
   while(start)
   {
      recordChar[len++] = start%10 + '0';
      start/=10;
   }
   if(len == 0)
       l = "0";
   for(int i = len-1;i >= 0;i--)
       l += recordChar[i];
   start = (n-1)*10 + 10 - 1;
   len = 0;
   while(start)
   {
       recordChar[len++] = start%10 + '0';
       start/=10;
   }
   for(int i = len - 1;i >= 0;i--)
       r += recordChar[i];
   mysql_real_connect(&mysql,"localhost","root","password","Supermarket",0,NULL,0);
   string sql = "select * from goods where name = \'" + searchstr + "\'" + " limit "+l+","+r;
    mysql_query(&mysql,sql.c_str());
    res = mysql_use_result(&mysql);
    Goods rec;
    if(res)
    {
       for(int i = 0;i < mysql_field_count(&mysql);i ++)
       {
    	   row = mysql_fetch_row(res);
	   if(row <= 0)break;
           rec.goods_id = row[0];
           rec.price = row[1];
           rec.stack = row[2];
           rec.place = row[3]?row[3]:"NULL";
           rec.image = row[4]?row[4]:"NULL";
           rec.description = row[5]?row[5]:"NULL";
           rec.class_id = row[6];
           rec.name = row[7];
    	   p->push_back(rec);
       }
    }else 
    {
        mysql_close(&mysql);
    }
   mysql_free_result(res);
   mysql_close(&mysql);
	return p;
}
class Customer :public User
{
public:
    Customer(){}
    Customer(int id){}
    Customer(string account){}
    vector<Cart>* GetCartList(int n);//结帐,n是显示第n页
    bool AddGoods(string Goods_id,string count);//购物车添加
    bool DelGoods(string Goods_id);//购物车删除
};
bool Customer::DelGoods(string goodid)
{
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    mysql_init(&mysql);
    mysql_real_connect(&mysql,"localhost","root","password","Supermarket",0,NULL,0);
    string sql = "select * from orderform where user_id =";             
    sql = sql + "\'" + user_id + "\'";
    mysql_query(&mysql,sql.c_str());
    res = mysql_use_result(&mysql);
    if(res==0)
    {
        mysql_free_result(res);
        return 0;
    }
    mysql_free_result(res);
    sql = string("select order_item_id from orderitem where goods_id=\'") + goodid + "\'";
    mysql_query(&mysql,sql.c_str());
    res = mysql_use_result(&mysql);
    if(res == 0){
        mysql_free_result(res);
        return 0;
    }
       
   row = mysql_fetch_row(res);
   string key(row[0]);

   mysql_free_result(res);
   sql = string("delete from orderitem where order_item_id=\'")+key+"\'";
   mysql_query(&mysql,sql.c_str());
   res = mysql_use_result(&mysql);
   mysql_free_result(res);
   mysql_close(&mysql);
   return 1;
}
bool Customer::AddGoods(string goodid,string count)
{
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    mysql_init(&mysql);
    mysql_real_connect(&mysql,"localhost","root","password","Supermarket",0,NULL,0);
    string sql = "select * from orderform where user_id =";             
    sql = sql + "\'" + user_id + "\'";
    mysql_query(&mysql,sql.c_str());
    res = mysql_store_result(&mysql);
    if(mysql_num_rows(res) == 0)
    {
        sql = string("insert into orderform(order_id,user_id) values(uuid(),") +"\'" + user_id + "\')";
        mysql_query(&mysql,sql.c_str());
        res = mysql_use_result(&mysql);
        mysql_free_result(res);
    }
    
    mysql_free_result(res);
    //获取order_id参数
    sql = string("select order_id from orderform where user_id=")+"\'"+user_id+"\'";
    mysql_query(&mysql,sql.c_str());
    res = mysql_use_result(&mysql);
    row = mysql_fetch_row(res);
    string orderid(row[0]);
    mysql_free_result(res);

    //判断对应订单里面是否存在对应的商品
    sql = string("select count from orderitem where order_id=\'") + orderid +"\'";
    mysql_query(&mysql,sql.c_str());
    res = mysql_store_result(&mysql);
    if(mysql_num_rows(res)!= 0)
    {
        row = mysql_fetch_row(res);
        int cnt = atoi(row[0]) + 1;
        mysql_free_result(res);
        string number="";
        char rec[333];
        int len = 0;
        while(cnt)
        {
            rec[len++] = cnt%10 + '0';
            cnt/=10;
        }
        for(int i = len - 1;i >= 0;i --)
            number +=rec[i]; 
        sql = string("update orderitem set count=")+number+" where order_id=\'" + orderid+"\'";
        mysql_query(&mysql,sql.c_str());
        res = mysql_use_result(&mysql);
        mysql_free_result(res);
        return 0;
    }
    mysql_free_result(res);
     //获取price参数
    sql =string("select price from goods where goods_id = ")+"\'"+goodid+"\'"; 
    mysql_query(&mysql,sql.c_str());
    res = mysql_use_result(&mysql);
    row = mysql_fetch_row(res);
    string price(row[0]);
    mysql_free_result(res);
    
    //对order_item插入商品
    sql = "insert into orderitem values(uuid(),\'"+price+"\',"+ count+",\'"+orderid+"\',\'"+goodid + "\')";
    mysql_query(&mysql,sql.c_str());
    mysql_free_result(mysql_use_result(&mysql)); 
    mysql_close(&mysql);
 
    return 1; 
}
vector<Cart>* Customer::GetCartList(int n)
{
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    mysql_init(&mysql);
    mysql_real_connect(&mysql,"localhost","root","password","Supermarket",0,NULL,0);
    //获取分页区间
   string l = "",r = "";
   char recordChar[33];
   int len = 0,start = (n-1);
   while(start)
   {
      recordChar[len++] = start%10 + '0';
      start/=10;
   }
   if(len == 0)
       l = "0";
   for(int i = len-1;i >= 0;i--)
       l += recordChar[i];
   start = (n-1)*10 + 10 - 1;
   len = 0;
   while(start)
   {
       recordChar[len++] = start%10 + '0';
       start/=10;
   }
   for(int i = len - 1;i >= 0;i--)
       r += recordChar[i];
 
    string sql("select price,goods.name,classification.name,count from goods join classification join orderitem join orderform where user_id =\'");
    sql = sql + user_id + "\'" + " limit "+l+","+r;
    mysql_query(&mysql,sql.c_str());
   res = mysql_use_result(&mysql);
   vector<Cart> *p = new vector<Cart>;
   Cart rec;
   if(res)
   {
       for(int i = 0;i < mysql_field_count(&mysql);i ++)
       {
           row = mysql_fetch_row(res);
           if(row <= 0)break;
           rec.price = row[0];
           rec.GoodsName = row[1];
           rec.Class = row[2];
           rec.count = row[3];
           (*p).push_back(rec);
       }
       mysql_free_result(res);
   }
   mysql_close(&mysql);
   return p;
}
class Administrator :public User
{
public:
    Administrator();
    Administrator(int id);
    Administrator(string account);
    vector<Classification>* getSubClass(string classid);
    vector<Customer>* CustomerList(int n);//用户列表
    bool delCustomer(string userid);//删除用户
    vector<Classification>* ClassList(int n);//分类列表
    bool AddClass(map<string,string> *parameter);//添加分类
    bool delClass(string classid);//删除分类
    //string ChangeStackInfo(Classification Class);//修改分类
    vector<Stack>* StackInfo(int n);//库存查看
    bool DelStack(string Goods_id);//减少库存
    bool AddStack(Goods* goods);//添加库存
//    bool ChangeStackInfo(Goods* goods);//修改商品
};
vector<Classification>* getSubClass(string classid)
{
    vector<Classification> *p = new vector<Classification>();
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    mysql_init(&mysql);
    mysql_real_connect(&mysql,"localhost","root","password","Supermarket",0,NULL,0);
   string sql = "select class_id,name from classification where pid ";
   if(classid == "")
   {
      sql = sql + " is null";
   }else sql = sql + "= \'"+classid + "\'";

   cout<<sql<<endl;
   mysql_query(&mysql,sql.c_str());
   res = mysql_use_result(&mysql);
   Classification rec;
   if(res)
   {
       for(int i = 0;i < mysql_field_count(&mysql);i ++)
       {
           row = mysql_fetch_row(res);
           if(row == 0)break;
           rec.class_id = row[0];
           rec.name = row[1];
           (*p).push_back(rec);
       }
   }
   mysql_free_result(res);
   mysql_close(&mysql);
   return p;
}
 bool DelStack(string Goods_id)//减少库存
{
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    mysql_init(&mysql);
    mysql_real_connect(&mysql,"localhost","root","password","Supermarket",0,NULL,0);
    string sql="update goods set stack=0 where goods_id=\'" + Goods_id+"\'";
    mysql_query(&mysql,sql.c_str());
    mysql_free_result(mysql_use_result(&mysql));
    mysql_close(&mysql);
 
    return 1;
}
bool Administrator::AddStack(Goods* goods)//添加库存
{
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    mysql_init(&mysql);
    mysql_real_connect(&mysql,"localhost","root","password","Supermarket",0,NULL,0);
    string sql = "insert into goods values(uuid(),";
    sql = sql + "\'" + (*goods).price+"\',\'" + (*goods).stack +"\',\'"+(*goods).place+"\',\'"+(*goods).image+"\',\'"+(*goods).description +"\',\'"+(*goods).class_id +"\',\'"+(*goods).name+"\')";
    mysql_query(&mysql,sql.c_str());
    res = mysql_store_result(&mysql);
    mysql_free_result(res);
    mysql_close(&mysql);
    return 1;
}
vector<Stack>* Administrator::StackInfo(int n)//库存查看
{
    vector<Stack> *p = new vector<Stack>();
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    mysql_init(&mysql);
    mysql_real_connect(&mysql,"localhost","root","password","Supermarket",0,NULL,0);
    //获取分页区间
   string l = "",r = "";
   char recordChar[33];
   int len = 0,start = (n-1);
   while(start)
   {
      recordChar[len++] = start%10 + '0';
      start/=10;
   }
   if(len == 0)
       l = "0";
   for(int i = len-1;i >= 0;i--)
       l += recordChar[i];
   start = (n-1)*10 + 10 - 1;
   len = 0;
   while(start)
   {
       recordChar[len++] = start%10 + '0';
       start/=10;
   }
   for(int i = len - 1;i >= 0;i--)
       r += recordChar[i];
 
    string sql ="select goods.name,classification.name,price,stack from goods join classification on goods.class_id = classification.class_id";
    sql = sql + " limit "+l +","+r;
    Stack rec;
    mysql_query(&mysql,sql.c_str());
    res = mysql_use_result(&mysql);
    if(res)
    {
        for(int i = 0;i < mysql_field_count(&mysql);i ++)
        {
            row = mysql_fetch_row(res);
            if(row == 0)break;
            rec.GoodsName = row[0];
            rec.Class = row[1];
            rec.price = row[2];
            rec.stack = row[3];
            (*p).push_back(rec);
        }
    }
    mysql_free_result(res);
    mysql_close(&mysql);
    return p;
}
bool Administrator::delClass(string classid)//删除分类
{
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    mysql_init(&mysql);
    mysql_real_connect(&mysql,"localhost","root","password","Supermarket",0,NULL,0);
   
}
bool Administrator::AddClass(map<string,string>* parameter)//添加分类
{
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    mysql_init(&mysql);
    mysql_real_connect(&mysql,"localhost","root","password","Supermarket",0,NULL,0);
    string sql;
    if((*parameter)["pid"] != "")
    {
        sql = "insert into classification (class_id,name,pid) values(uuid(),";   
        sql = sql + "\'" + (*parameter)["name"] + "\',\'" + (*parameter)["pid"] + "\'" + ")";
    }else 
    {
         sql = "insert into classification (class_id,name) values(uuid(),";   
        sql = sql + "\'" + (*parameter)["name"] + "\'" + ")";
    }
    mysql_query(&mysql,sql.c_str());
    res = mysql_use_result(&mysql);
    mysql_free_result(res);
    mysql_close(&mysql);
    return true;
}
vector<Classification>* Administrator::ClassList(int n)//分类列表
{
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    mysql_init(&mysql);
    mysql_real_connect(&mysql,"localhost","root","password","Supermarket",0,NULL,0);
 
    vector<Classification>*p = new vector<Classification>();
    //获取分页区间
   string l = "",r = "";
   char recordChar[33];
   int len = 0,start = (n-1);
   while(start)
   {
      recordChar[len++] = start%10 + '0';
      start/=10;
   }
   if(len == 0)
       l = "0";
   for(int i = len-1;i >= 0;i--)
       l += recordChar[i];
   start = (n-1)*10 + 10 - 1;
   len = 0;
   while(start)
   {
       recordChar[len++] = start%10 + '0';
       start/=10;
   }
   for(int i = len - 1;i >= 0;i--)
       r += recordChar[i];
    string sql = "select * from classification";  
    Classification rec;
    mysql_query(&mysql,sql.c_str());
    res = mysql_use_result(&mysql);
    if(res)
    {
        for(int i = 0;i < mysql_field_count(&mysql);i ++)
        {
            row = mysql_fetch_row(res);
            if(row == 0)break;
            rec.class_id = row[0];
            rec.name = row[1];
            rec.pid = row[2]?row[2]:"NULL";
            (*p).push_back(rec);
        }
    }
    mysql_free_result(res);
    mysql_close(&mysql);
    return p;
}
bool Administrator::delCustomer(string userid)//删除用户
{
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    mysql_init(&mysql);
    mysql_real_connect(&mysql,"localhost","root","password","Supermarket",0,NULL,0);
  string sql = string("select * from user where user_id=\'") + userid +"\'";
  mysql_query(&mysql,sql.c_str());
  res = mysql_store_result(&mysql);

  if(mysql_num_rows(res) == 0)
  {
      mysql_free_result(res);
      return 0;
  }
   mysql_free_result(res);

   sql = string("select order_id from orderform where user_id=\'")+userid+"\'";
   mysql_query(&mysql,sql.c_str());
   res = mysql_store_result(&mysql);
  if(mysql_num_rows(res) == 0)
  {
      mysql_free_result(res);
      return 0;
  }
    
   if(res)
   {
     string orderid;
     row = mysql_fetch_row(res);
     orderid = row[0];
     mysql_free_result(res);

      //删除表orderitem对应内容;
      sql = "delete from orderitem where order_id=\'"+orderid+"\'";
     mysql_query(&mysql,sql.c_str());
     mysql_free_result(mysql_use_result(&mysql));
    
     //删除表orderform对应内容
     sql = "delete from orderform where order_id=\'"+orderid+"\'";
     mysql_query(&mysql,sql.c_str());
     mysql_free_result(mysql_use_result(&mysql));

     //删除user表对应内容
       sql = "delete from user where user_id=\'" + userid + "\'";
       mysql_query(&mysql,sql.c_str());
       mysql_free_result(mysql_use_result(&mysql));
    
       mysql_close(&mysql);
   }else
   {
       mysql_free_result(res);
       mysql_close(&mysql);
   }
    return 1;
}
vector<Customer>* Administrator::CustomerList(int n)
{
    vector<Customer>* p = new vector<Customer>;
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    mysql_init(&mysql);
    mysql_real_connect(&mysql,"localhost","root","password","Supermarket",0,NULL,0);
    
   string l = "",r = "";
   char recordChar[33];
   int len = 0,start = (n-1);
   while(start)
   {
      recordChar[len++] = start%10 + '0';
      start/=10;
   }
   if(len == 0)
       l = "0";
   for(int i = len-1;i >= 0;i--)
       l += recordChar[i];
   start = (n-1)*10 + 10 - 1;
   len = 0;
   while(start)
   {
       recordChar[len++] = start%10 + '0';
       start/=10;
   }
   for(int i = len - 1;i >= 0;i--)
       r += recordChar[i];
   string sql("select * from user limit ");
   sql = sql + l + ","+r;
   mysql_query(&mysql,sql.c_str());
   res = mysql_use_result(&mysql);
   Customer rec;
   if(res)
   {
        for(int i = 0;i < mysql_field_count(&mysql);i ++)
        {
            row = mysql_fetch_row(res);
            if(row == 0)break;
            rec.user_id = row[0];
            rec.account = row[1];
            rec.password = row[2];
            rec.name = row[3]?row[3]:"NULL";
            rec.phone = row[4]?row[4]:"NULL";
            rec.address = row[5]?row[5]:"NULL";
            (*p).push_back(rec);
        }
   }
  mysql_free_result(res);
  mysql_close(&mysql);
  return p; 
}
User* login(string account,string password)
{
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    mysql_init(&mysql);
    mysql_real_connect(&mysql,"localhost","root","password","Supermarket",0,NULL,0);
    string sql ="select * from user where account=";
    sql = sql + " \'" + account + "\' and password=\'" + password+"\'";
    mysql_query(&mysql,sql.c_str());
    res = mysql_store_result(&mysql);
    if(mysql_num_rows(res) == 0)
    {
        mysql_free_result(res);
        mysql_close(&mysql);
        return NULL;
    }
    User *p = new User();
    User &rec = *p;
    for(int i = 0;i < mysql_field_count(&mysql);i ++)
    {
       row = mysql_fetch_row(res);
       if(row == 0)break;
       rec.user_id = row[0];
       rec.account = row[1];
       rec.password = row[2];
       rec.name = row[3]?row[3]:"NULL";
       rec.phone = row[4]?row[4]:"NULL";
       rec.address = row[5]?row[5]:"NULL";    
    }
    
   mysql_free_result(res);
   mysql_close(&mysql);
   return p; 
}
bool userRegister(User *user)
{
    string account = (*user).account;
    string password = user->password;
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;
    mysql_init(&mysql);
    mysql_real_connect(&mysql,"localhost","root","password","Supermarket",0,NULL,0);
    string sql ="select * from user where account=";
    sql = sql + " \'" + account + "\' and password=\'" + password+"\'";
    mysql_query(&mysql,sql.c_str());
    res = mysql_store_result(&mysql);
    if(mysql_num_rows(res) == 0)
    {
        mysql_free_result(res);
        mysql_close(&mysql);
        return 0;
    }
    
        mysql_free_result(res);
        mysql_close(&mysql);
        return 1;
}
int main()
{
  return 0;
}
