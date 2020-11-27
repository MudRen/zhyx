// ����ʦ

inherit NPC;
#include <ansi.h>;
int begin_paimai(string name,int value ,int paimai_count,int m);
int go_paimai(string id,string name,int value,int num,int m);
int report_paimai(object buyer,int money,int num);
int finish_paimai(int num,int sign);
int pay_back(string id, int amount);
int delete_ob(int num);
string to_ch(int money);
void create()
{
        set_name("����ʦ", ({ "paimai shi", "ji", "shi" }) );
                set("nickname", HIY+BLINK "���µ�һ��" NOR);
        set("gender", "����");
        set("age", 45);
        set("no_get", 1);
        set("long",
                "����һλ�ݸߵ������ˣ���Ϊ������˽������Ϊ���µ�һ����ʦ��\n");
        set("combat_exp",600000);
        set("shen", 0);
            set("attitude", "friendly");

        set("apply/attack", 100);
        set("apply/defense", 100);

        set("max_qi", 800);
        set("qi", 800);
        set("max_jing", 800);
        set("jing", 800);
        set("max_jingli", 800);
        set("jingli",800);
        set("max_neili", 8000);
        set("neili",8000);
        
        set_skill("force", 300);
        set_skill("unarmed", 300);
        set_skill("sword",300);
        set_skill("parry",300);
        set_skill("dodge", 300);

            setup();

        carry_object("/clone/cloth/cloth")->wear();
}


void init()
{
        ::init();
        add_action("do_paimai", "paimai");
        add_action("do_paimailist", "paimailist");
        add_action("do_yao", "yao");
        
}
int do_paimai(string arg)
{
        object who,ob;
        int money,clone_number,paimai_count,i,value,sale_price;
        string id,file_name;
        mapping fpaimai,vpaimai,ipaimai,npaimai,lpaimai,opaimai,spaimai;
        string* terms;
        
        fpaimai = query("fpaimai");
        vpaimai = query("vpaimai");
        ipaimai = query("ipaimai");
        npaimai = query("npaimai");
        lpaimai = query("lpaimai");
        opaimai = query("opaimai");
        spaimai = query("opaimai");
        
        who=this_player();
        
        if( who->is_busy() )
         return notify_fail("��Ķ�����û����ɣ������ύ��Ʒ����������\n");
        if( who->query_condition("auction_forbindden"))
                return notify_fail("��Ŀǰ���ܲ���������\n");
    if( !arg || sscanf(arg, "%s with %d",id, money)!=2 )
                return notify_fail("ָ���ʽ��paimai <��Ʒid> with <�׼�(silverΪ��λ)> \n");
        if( !ob=present(id, who))
                return notify_fail("������û������������\n");
        if( ob->query("money_id") )     
                return notify_fail("��Ҫ������Ǯ����\n");
        if (ob->query("value")<10 || money==0)
                return notify_fail("����ʦ˵�������������ֵǮ����ͱ����ˣ�\n");
        if (ob->query("no_sell")&&!ob->query("can_auction"))
                return notify_fail("����ʦ˵���������������������ˣ�\n");
        if (ob->query("no_drop")&&!ob->query("can_auction"))
                return notify_fail("����ʦ˵�����Ӳ����Ķ������������㵱�������������Ѱ���\n");
        if( ob->query_unique() && !ob->query("can_auction") )
                return notify_fail("����ʦ˵����˵�����ǹ�Ʒ������������ɲ��ҳн���������ˣ�\n");
    if(money<(100+ob->query("value")/100))
                return notify_fail("����ʦ˵�����������Ȿ���⣬�ٺ٣����ƴ���������ν��С�����������Ҫ����ġ�\n");
    if(money<0||money>1000000)
                return notify_fail("����ʦ˵��������ļ۸��ǷǷ��ġ�\n"); //��ֹ���
        if (who->query("balance")<10000)
                return notify_fail("����ʦ˵�������˺����Ǯ����֧�������ѣ�\n");
   
        who->add("balance",-10000);
        command("sys "+who->query("name")+"("+who->query("id")+")"+NOR+ob->query("name")+HIC+"����������\n"NOR);
        command("chat "+"�����ύ"+NOR+ob->query("name")+HIC+"������������ʹ��"+HIW"��"HIG" ��  �� "HIW"��"NOR+HIC"Ƶ��"HIY"���£ɣ̣̣�"HIC"�˽���������"NOR);
    who->apply_condition("auction_forbindden",1+random(10));
        sscanf(file_name(ob),"%s#%d",file_name,clone_number);

        if( mapp(fpaimai) &&  sizeof(fpaimai) )
                add("total_number",1);
        else
                set("total_number",0);
        
        value = ob->query("value");
        sale_price= ob->query_temp("sale_price");
        if (sale_price>0)
                sale_price= sale_price>value?value:sale_price;

        set("fpaimai/"+ sprintf("%d",query("total_number")),file_name);
        set("vpaimai/"+sprintf("%d",query("total_number")), money);
        set("ipaimai/"+sprintf("%d",query("total_number")), who->query("id"));
        set("npaimai/"+sprintf("%d",query("total_number")), ob->query("name"));
        set("lpaimai/"+sprintf("%d",query("total_number")), 1);
        set("opaimai/"+sprintf("%d",query("total_number")), who->query("id"));
        set("spaimai/"+sprintf("%d",query("total_number")), sale_price);
        
        if (query("total_number")==0 || query("lpaimai/"+sprintf("%d",query("number")))==0)
        {
                set("value",money);
                set("pnum",0);
                set("number",query("total_number")>0?query("number")+1:0);
                call_out("begin_paimai",5,ob->query("name"),money,query("number"),0);
        }
        
        if(!ob->query_unique())
                destruct(ob); 
        else
        {
                ob->move(this_object());
                call_out("destobj",700,ob);
        }
        return 1;
}
void destobj(object ob)
{
        if(!ob)
                return;
    destruct(ob); 
}
int begin_paimai(string name,int money,int num,int m)
{
        string mon;
        m+=1;
        if (m==1)
        {
                command("bill "+"���ڿ�ʼ���� "NOR+name+HIG+" ������Ȩ��"+NOR);
        }
        set("on_paimai",1);
        mon = to_ch(money);
        command("bill "+NOR+name+HIG+"�׼�"+mon+"��"+chinese_number(m)+"��");
        command("bill "+name+HIG"�Ǳ���ڡ�"+chinese_number(num)+"��������Ʒ����������ʹ�ã£ɣ�������о���\n"NOR);

        if (!(m==3))
                call_out("begin_paimai",20,name,money,num,m);
        else
                call_out("finish_paimai",2,num,0);      
}
int finish_paimai(int num,int sign)
{
        string id,owner_id;
        object buyer,owner;
        int i;

        
        id=query("ipaimai/" + sprintf("%d", num));
        owner_id=query("opaimai/" + sprintf("%d", num));
        set("lpaimai/"+sprintf("%d",num), 0);
                
        buyer=find_player(id);
        owner=find_player(owner_id);
        if (sign==0)
        {
                command("bill "+query("npaimai/" + sprintf("%d", num))+HIG+" ������Ȩ���������ˡ�"+NOR);
                if(owner)
                        tell_object(owner,HIR"��Ķ���û������ȥ������ʮ����������������ȡ���Լ�����Ʒ��\n"NOR);
        }
        else            
        {
        if(!buyer->query_temp("invisibility_buyer"))
        {
                command("bill  �ɽ�!"+buyer->query("id")+"����� "+NOR+query("npaimai/" + sprintf("%d", num))+HIG+" ������Ȩ��"+NOR);
        }
        else
        {
                command("bill �ɽ�! ���˻���� "+NOR+query("npaimai/" + sprintf("%d", num))+HIW+" ������Ȩ��"+NOR);
                command("sys  �ɽ�!"+buyer->query("id")+"����� "+NOR+query("npaimai/" + sprintf("%d", num))+HIG+" ������Ȩ��"+NOR);
        }
                if (buyer)
                        tell_object(buyer,HIR"������ "+NOR+query("npaimai/" + sprintf("%d", num))+HIR+" ������Ȩ������ʮ��������������ȡ������Ķ�����\n"NOR);
                if (owner)
                        tell_object(owner,HIR"���"+NOR+query("npaimai/" + sprintf("%d", num))+HIR+"����"
                        +chinese_number(query("vpaimai/" + sprintf("%d", num)))+"�����ӣ��۳�5%�����ѣ�������Ѿ�������Ļ�ͷ�ˡ�\n"NOR);        
        }
    if(buyer)
          buyer->apply_condition("auction_forbindden",1+random(10));
        set("on_paimai",0);
        
        if (query("pnum"))
            pay_back(owner_id,query("vpaimai/" + sprintf("%d", num))*95);
                        if(!who->restore())
                {
                        log_file("paimai_log","Failed to return "+amount+
                                " coin to "+id+"\n");
                        destruct(who);
                        return 0;
                }
                else 
                {
                        who->add("balance",amount);
                        if(!who->save(1))
                        { // save(1) will not erase autoload.
                                log_file("paimai_log","Failed to return "+amount+
                                        " coin to "+id+"\n");
                                destruct(who);
                                return 0;
                        } 
                        log_file("paimai_log","pay "+amount+" to "+id+"\n");
                        destruct(who);
                        return 1;
                }
    }
}
int go_paimai(string id,string name,int money,int num,int m)
{
        string mon;
        m+=1;
        mon = to_ch(money);
        command("bill "+id+" ���� "+mon+"���� "+NOR+name+HIG+" ������Ȩ����"+chinese_number(m)+"��");
        command("bill "+name+HIG"�Ǳ���ڡ�"+chinese_number(num)+"��������Ʒ����������ʹ�ã£ɣ�������о���\n"NOR);
        if (!(m==3))
                call_out("go_paimai",20,id,name,money,num,m);
        else
                call_out("finish_paimai",5,num,1);      
}
int do_paimailist()
{
        int i;
        
        for(i=query("number")+1;;i++)
        {
                if (query("lpaimai/" + sprintf("%d", i))==1)
                {
                        printf("%-10s�� �׼� %-3d ������ \n",query("npaimai/" + sprintf("%d", i)),query("vpaimai/" + sprintf("%d", i)));
                }
                else
                        return 1;
        }
        return 1;
}
int do_yao()
{
        mapping fpaimai,vpaimai,ipaimai,npaimai,lpaimai,spaimai;
        string* terms;
        string id;
        object ob;
        int i;

        fpaimai = query("fpaimai");
        vpaimai = query("vpaimai");
        ipaimai = query("ipaimai");
        npaimai = query("npaimai");
        lpaimai = query("lpaimai");
        spaimai = query("spaimai");
        
        if( mapp(fpaimai) &&  sizeof(fpaimai) )
        {
                terms=keys(fpaimai);
        
                for(i=0;i<sizeof(terms);i++)
                {
                        if (ipaimai[terms[i]]==this_player()->query("id") && lpaimai[terms[i]]==0)
                        {
                                ob=new(fpaimai[terms[i]]);
                                if (spaimai[terms[i]]>0)
                                        ob->set_temp("sale_price",spaimai[terms[i]]);
                                ob->move(this_player());
                                if(ob->query_unique()||ob->query("can_auction"))
                                        ob->set("can_auction",0);
                                ipaimai[terms[i]]="paimai shi";
                                message_vision(CYN+"����ʦ��"+NOR+npaimai[terms[i]]+CYN+"����$N��\n"NOR, this_player(),this_object());
                                return 1;
                        }
                }
        }
        tell_object(this_player(),"����û�����������Ʒ��\n");
        return 1;
}
int delete_ob(int num)
{
        delete("npaimai/"+sprintf("%d",num));
        delete("ipaimai/"+sprintf("%d",num));
        delete("vpaimai/"+sprintf("%d",num));
        delete("lpaimai/"+sprintf("%d",num));
        delete("fpaimai/"+sprintf("%d",num));
        delete("spaimai/"+sprintf("%d",num));
        
        return 1;
}

string to_ch(int money)
{
        int gold,silver;
        string mon;
        gold = money/100;
    if(gold)
                mon =chinese_number(gold)+"���ƽ�";
        silver = money-gold*100;
        if(silver)
                mon +="��"+chinese_number(silver)+"������";
        mon +="("+sprintf("%d",money)+" silver)";
    set_temp("price",mon);
    return mon;
}
        
        call_out("delete_ob",600,num)
        num=num+1
        if (query("lpaimai/" + sprintf("%d", num))==1
        
                set("value",query("vpaimai/" + sprintf("%d", num)))
                set("number",num)
                set("pnum",0)
                call_out("begin_paimai",5,query("npaimai/" + sprintf("%d", num)),query("vpaimai/" + sprintf("%d", num)),num,0)
        
        return 1
int report_paimai(object buyer,int money,int num
        string mon
        remove_call_out("begin_paimai")
        remove_call_out("finish_paimai")
        remove_call_out("go_paimai")
       
        if(query("pnum")) // pnum���ж��Ƿ�����Ͷ��ı�־��
        
                pay_back(query("ipaimai/" + sprintf("%d", num)),query("vpaimai/" + sprintf("%d", num))*100);//�黹ǰһ�������ߵ�Ǯ�
                add("pnum",1)
        
        buyer->add("balance",(0-money*100))
        set("vpaimai/"+sprintf("%d",num), money)
        set("ipaimai/"+sprintf("%d",num), buyer->query("id"))
        set("value",money)
        mon =to_ch(money)
        if(!buyer->query_temp("invisibility_buyer")
        
           if (!query("pnum")
                   add("pnum",1)
                command("bill  "+buyer->query("id")+" ���� "+mon+"����"+NOR+query("npaimai/" + sprintf("%d", num))+HIG"������Ȩ��")
        call_out("go_paimai",5,buyer->query("name")+"("+buyer->query("id")+")",query("npaimai/" + sprintf("%d", num)),money,num,0)
        
        els
        
           if (!query("pnum")
           add("pnum",1)
       command("sys  "+buyer->query("id")+" ���� "+mon+"����"+NOR+query("npaimai/" + sprintf("%d", num))+HIG"������Ȩ��")
       command("bill  ���˳��� "+chinese_number(money)+"������ ����"+NOR+query("npaimai/" + sprintf("%d", num))+HIG"������Ȩ��")
       call_out("go_paimai",5,"ĳ��",query("npaimai/" + sprintf("%d", num)),money,num,0)
        
        return 1
int pay_back(string id, int amount
    object who
   
    who=find_player(id)
    if(who
        
                who->add("balance",amount)
                if(!who->save(1))
                
                        log_file("paimai_log","Failed to return "+amount
                                " coin to "+id+"\n")
                        return 0
                
        log_file("paimai_log","pay "+amount+" to "+id+"\n")
        return 1
    }
        els
        
                who=new(USER_OB)
                who->set("id",id)
