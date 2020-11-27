// jinyong.c ��ӹ

inherit NPC;
#include <ansi.h>;
#define  LEITAI             "/u/sanben/leitai/leitai"

int do_bihua(string arg);
int do_no();
void shout_message(string msg);
int accept_object(object me, object ob);
int ask_award();

void create()
{       int i;
        object master;
        set_name(HIY "��ӹ" NOR, ({ "jin yong", "jin", "yong" }) );
        set("title", HIG"����ʼ��" NOR);
        set("nickname", HIC"һ֧��ʾ��滳"NOR);
        set("gender", "����");
        set("age", 35);
        set("no_get", 1);
        set("long",
           "�������������Ĵ�ʼ�˽�ӹ�������\n");
        set("attitude", "friendly");       

        for(i = 1; i < 6; i++)
        {
           master = new("/u/sanben/leitai/npc" + i);
           master->restore();
           set("idlist/" + i, master->query("id"));
           set("namelist/" + i, master->query("name"));        
           destruct(master);
        }
        set("inquiry", ([ 
            "����̨" : "Ҫ����̨���ȸ���ʮ���ƽ���ҡ�",                          
            "��̨"   : "Ҫ����̨���ȸ���ʮ���ƽ���ҡ�",                          
            "����"   : "Ҫ����̨���ȸ���ʮ���ƽ���ҡ�",              
            "����"   : ( : ask_award : ),                        
         ])); 
        setup();       
        carry_object("/clone/misc/cloth")->wear();      
}


void init()
{
        ::init();   
                  
        add_action("do_bihua", "bihua");
        add_action("do_bihua", "fight");
        add_action("do_no", "beg");
        add_action("do_no", "steal");
        add_action("do_no", "quanjia");
        add_action("do_no", "persuade");
        add_action("do_no", "touxi");
        add_action("do_no", "ansuan");
        add_action("do_no", "kill");
        add_action("do_no", "hit");  
        add_action("do_no", "crattack");  
        add_action("do_no", "spattack");  
        add_action("do_no1", "auction");  
        add_action("do_no1", "du");           
        add_action("do_no1", "study");    
        add_action("do_no1", "read");                                    
        add_action("do_no1", "summon");
        add_action("do_no1", "eat");
        add_action("do_no1", "drink");
        add_action("do_ready", "ready");
        add_action("re_set","reset");      
        add_action("set_wp","setwp");
        add_action("set_pfm","setpfm");
        add_action("set_ok","setok");
        add_action("re_set","reset"); 

        add_action("do_du", "du");
        add_action("do_du", "study");        
}

int do_du()
{
    write("���䳡����ֹ����!\n");
    return 1;
}

int ask_award()
{
    int i, flag;
    int pot, tihui;
    string msg;

    object me;

    me = this_player();
    flag = 0;     

    for(i = 1; i < 6; i++)
    {
       if ( query("idlist/" + i) == me->query("id") ) 
       {        
          flag = i;
          break;
       }
    }
   
    if ( flag == 0 ) 
    {
       command("say ���ֲ���������֮һ����ʲô����!");
       return 1;
    }

    if ( time() - me->query("leitai/time") < 24 * 3600)
    {
       command("say �������סһ����̨�����н���!");
       return 1;
    } 

    if ( time() - me->query("leitai/last_award") < 24 * 3600 )
    {
       command("say 24Сʱ��ֻ��Ҫһ�ν���!");
       return 1;
    }

    command("say �ţ��õġ�\n");

    me->set("leitai/last_award", time());

    pot = 500 * flag + 1000 + random(200);
    tihui = 200 * flag + 1000 + random(100);

    if ( me->query("potential") >= me->query_potential_limit() )
       {  pot = 1; }
    if ( me->query("experience") >= me->query_experience_limit() )
       {  tihui = 1; }

    me->add("potential", pot);
    me->add("experience", tihui);

    msg = "����"NOR HIR + me->query("name") + NOR HIY"�ɹ���סһ����̨��\n"
          "            �ظ��轱��" + chinese_number(pot) + "��Ǳ�ܼ�" +
          chinese_number(tihui) + "��ʵս��ᡣ\n";  
    shout_message(msg);  
    return 1;
}


int set_wp(string arg)
{
    object me;
    me = this_player();

    if ( ! me->query_temp("leitai/set_start") ) return 0;

    if ( !arg ) return notify_fail("��������ʲô������\n");
    if ( me->delete_temp("leitai/set/wpe") )
         return notify_fail("���Ѿ����������ù������ˣ���������������reset��\n");
    me->delete_temp("leitai/setok");

    switch(arg)
    {

      case "��":
           me->set_temp("leitai/set/wpc","��");
           me->set_temp("leitai/set/wpe",
               load_object("/clone/weapon/axe"));
           break;
      case "��": 
           me->set_temp("leitai/set/wpc","��");
           me->set_temp("leitai/set/wpe",
               load_object("/d/luoyang/npc/obj/sword1"));
           break;
      case "��": 
           me->set_temp("leitai/set/wpc","��");
           me->set_temp("leitai/set/wpe",
               load_object("/clone/weapon/changbian"));
           break;
      case "����": 
           me->set_temp("leitai/set/wpc","����");
           me->set_temp("leitai/set/hand", 1);
           me->set_temp("leitai/set/wpe",
               load_object("/d/luoyang/npc/obj/hand"));
           break;
      case "��": 
           me->set_temp("leitai/set/wpc","��");
           me->set_temp("leitai/set/wpe",
               load_object("/clone/weapon/hammer"));
           break;
      case "��": 
           me->set_temp("leitai/set/wpc","��");
           me->set_temp("leitai/set/wpe",
               load_object("/d/luoyang/npc/obj/sword1"));
           break;
      case "��": 
           me->set_temp("leitai/set/wpc","��");
           me->set_temp("leitai/set/wpe",
               load_object("/clone/weapon/qimeigun"));
           break;
      case "ָ��": 
           me->set_temp("leitai/set/wpc","ָ��");
           me->set_temp("leitai/set/hand", 1);
           me->set_temp("leitai/set/wpe",
               load_object("/d/luoyang/npc/obj/finger"));
           break;
      case "��": 
           me->set_temp("leitai/set/wpc","��");
           me->set_temp("leitai/set/wpe",
               load_object("/clone/weapon/tiegun"));
           break;
     default :
           write(HIC"���õı��������ǡ����������ޡ����ơ�������������ָ�ס��ȡ�"
                 "���е�һ�֡�\n"NOR);
           return 1;
    } 
    write(HIG"\n������������������б���" + me->query_temp("leitai/set/wpe")->name()
          + "��\n"NOR);   
    if (me->query_temp("leitai/set/pfm"))        
        write(HIM"\n��������ú���������setok��\n"
              "ϵͳ��Ϊ���Զ�����������������Ժ��˵���ս��\n"NOR);  
    else 
        write(HIM"\n�������setpfm�������������ľ��С�\n"
              "��ʽ��setpfm taixuan-gong|unarmed|xuan\n"NOR);
    return 1;

}

int set_pfm(string arg)
{
    object me;
    string sk, type, pfm, *allpfm, *allpfm_ok, msg;
    int i;
    me = this_player();  
    msg = ""; 

    if ( ! me->query_temp("leitai/set_start") ) return 0;
    me->delete_temp("leitai/setok");

    if ( !arg || sscanf(arg, "%s|%s|%s", sk, type, pfm) != 3 ) 
       return notify_fail("��������ʲô���У�����:setpfm taixuan-gong|sword|jing\n");    

    if ( ! me->query("can_perform/" + sk + "/" + pfm) )
       return notify_fail(HIR"�㲢����ʹ����һ����ѽ��\n"
              "��ע���ʽΪsetpfm ��������|��������|��������\n"NOR);    

    if ( ! me->query_temp("leitai/set/pfm") )
    {
       allpfm = ({});
       allpfm_ok = ({});
    }
    else
    {
       allpfm = me->query_temp("leitai/set/pfm");
       allpfm_ok = me->query_temp("leitai/set/pfmok");
    }
    if ( sizeof(allpfm) > 2 )
        return notify_fail("�ܱ�Ǹ�����Ѿ����������������ˡ�\n������setok��"
                           "���������reset���������þ��С�\n");    
    if (member_array(sk + "|" + type + "|" + pfm, allpfm ) != -1 )
        return notify_fail("����������Ѿ����ù��ˡ�\n");    

    allpfm += ({ sk + "|" + type + "|" + pfm });  
    allpfm_ok += ({ type + "." + pfm });
 
    me->set_temp("leitai/set/pfm", allpfm); 
    me->set_temp("leitai/set/pfmok", allpfm_ok); 

    for (i = 0; i < sizeof(allpfm); i++ )
    {
         msg += allpfm[i] + "\n";   
     }
     write(HIG"\nĿǰ����������õľ���Ϊ��\n"NOR HIC + msg + "\n"NOR);     
     write(HIY"���Ѿ�Ϊ����������" + sizeof(allpfm) + "������\n"); 
     if ( sizeof(allpfm) < 3 )
         write(HIY"������ÿ�����������"NOR HIG+ "setok"NOR
                HIY"������������þ����������\n"NOR); 
     else
         write(HIR"���������������������ԵĻ�������" NOR HIG "setok" NOR
               HIR"�����������"NOR HIG + "reset" NOR 
               HIR"���������á�\n"NOR); 
     return 1;
}

int set_ok(string arg)
{
    object me;
    string msg1, msg2, *pfm;
    int i;
    me = this_player();  
    msg2 = "";

    if ( ! me->query_temp("leitai/set_start") ) return 0;
    if ( me->query_temp("leitai/setok") < 1 )
    {
       msg1 = me->query_temp("leitai/set/wpc");
       if (! msg1) msg1 = HIR"��"NOR;

       pfm = me->query_temp("leitai/set/pfm");
       if (! pfm) msg2 = HIR"    ��"NOR;
       else
          {
             for( i = 0; i < sizeof(pfm); i++ )
             {
                 msg2 += "    " + pfm[i] + "\n"; 
             }
          }  
        me->add_temp("leitai/setok", 1);   
        write("�����ڸ�������������������:\n"
              "����:\n    " + msg1 + "\n����:\n" + msg2 +
              "\n��������ԵĻ���������һ��setok�����������reset���������á�\n");
     }
     else
     {
        call_other(__FILE__, "finish", me);
     }
     return 1;
}

int re_set()
{
     object me;
     me = this_player();
     if ( ! me->query_temp("leitai/set_start") ) return 0;
     me->delete_temp("leitai/set");
     me->delete_temp("leitai/setok");
     write(HIY"������������������е����á�\n"NOR);
     return 1;
}

void finish(object me)
{
     object npc, npc1, master, mrt, *inv, *obj;
     string msg;
     int i, ii, level;

     level = me->query_temp("leitai/level");

     //��ԭ��������������������
     if ( me->query_temp("leitai/old_lvl") )     
         rm("/data/leitai/npc" + me->query_temp("leitai/old_lvl") + ".o");  
  
    for(i = 1; i < level; i++)
    {     
      if ( file_size("/data/leitai/npc" + (i + 1) + ".o") > 0 )
      {
          cp("/data/leitai/npc" + (i + 1) + ".o",
              "/data/leitai/npc" + i + ".o");  

          npc1 = new("/u/sanben/leitai/npc" + i);
          npc1->set("level",i);

         switch(i)
         {
          case 1 :
               npc1->set("nickname", HIC "��а" NOR );  
               break;          
          case 2 :
               npc1->set("nickname", HIR "����" NOR); 
               break;                      
          case 3 :
               npc1->set("nickname", HIY "�ϵ�" NOR);   
               break;                     
          case 4 :
               npc1->set("nickname", HIW "��ؤ" NOR);  
               break;                      
          case 5 :
               npc1->set("nickname", HIW "����ͨ" NOR);  
               break;                      
         }   
         npc1->save();
         destruct(npc1);
        if ( file_size("/data/leitai/npc" + (i + 2) + ".o") < 0 )
           rm("/data/leitai/npc" + (i + 1) + ".o"); 
      }      
    } 

     npc = new(__DIR__"npc" + level);
     if ( ! npc )
     {
         write(HIR"�޷������������������ϵ��ʦ��\n"NOR);
         return; 
     }   

     npc->do_copy(me);  
    
     npc->delete("weapon");           
     npc->delete("hand");     
     
     if (me->query_temp("leitai/set/wpe"))
     {
        if (me->query_temp("leitai/set/hand"))       
            npc->set("hand", base_name(me->query_temp("leitai/set/wpe")));       
    
        else
            npc->set("weapon", base_name(me->query_temp("leitai/set/wpe")));     
     }    
     
     npc->delete("pfm");
     npc->set("pfm", me->query_temp("leitai/set/pfmok"));

     npc->save();  
     npc->restore();   
   
    
     msg = "��ϲ"NOR HIR + me->name() + "(" + me->query("id") + ")"NOR
            HIY"�����һ��"NOR + npc->query("nickname") + NOR HIY"�ƺš�"NOR;
     shout_message(msg); 
     destruct(npc);

     for(i = 1; i < 6; i++)
     {
        master = new("/u/sanben/leitai/npc" + i);
        master->restore();
        set("idlist/" + i, master->query("id"));
        set("namelist/" + i, master->query("name"));       
        destruct(master);
     }
     
    //���²��ָ���������
    for( ii = 1; ii < 6; ii++)
    {
	if (mrt = find_object(__DIR__"mrt" + ii))
	{  	
          tell_room(mrt, HIR"����ͷ֪ͨ���������￪ʼ���죬�����˵�һ���뿪��\n\n"NOR);	
	   inv = all_inventory(mrt);
  	   for(i=0; i<sizeof(inv); i++)
          {
		if ( ! inv[i]->is_player() )
            	   destruct(inv[i]);
              else
              {
                 inv[i]->move("/d/city/guangchang");                
              }   
	    }          
	    destruct(mrt);
	}
     }

     if ( me )
     {
         me->delete_temp("leitai");
         me->set("leitai/time", time()); 
         tell_object(me, HIG"\n��ı��δ���Բ��������\n"NOR);       
     }  
}


int do_bihua(string arg)
{
        object me;
        object ob;
        object old;
        me = this_player();


        if ( ! me->query_temp("leitai") )
        {
                write("����û�ֵ������̨��\n");
                return 1;
        }
        if (! arg || ! objectp(ob = present(arg)))
        {
                write("��Ҫ��˭�Ȼ���\n");
                return 1;
        }
        if (me == ob)
        {
                write("���ǲ�����Ϊ���¾����Լ����ϴ���û�еڶ���Ӣ���ˡ�\n");
                return 1;
        }
        if ( userp(ob))
        {
                write("���ﲻ�ܽ�����Ҽ�ı��ԡ�\n");
                return 1;
        }
        if ( base_name(ob) == __DIR__"jinyong" )
        {
                write("������ǲ��У��������ʲô��!\n");
                return 1;
        }

        if (! living(ob))
        {
                write("�㻹�ǵ��˼�������˵�ɡ�\n");
                return 1;
        }
        if (me->is_fighting() && me->query_competitor())
        {
                write("���������ں�" + me->query_competitor()->name() +
                      "�����ء�\n");
                return 1;
        }
        if (ob->is_fighting())
        {
                write("�˼����ڶ��֣�����ȥ���ָ�ʲô��\n");
                return 1;
        }
        if (me->query("qi") * 100 / me->query("max_qi") < 70)
        {
                write("�����������������棬�α�æ�Ŷ��֣�\n");
                return 1;
        }
        if (ob->query("qi") * 100 / ob->query("max_qi") < 70)
        {
                write("�˼������ƺ�������֧�����ǵȻ����˵�ɡ�\n");
                return 1;
        }
        message_vision(HIY "\n$N" HIY "��$n��ͷ�����ܺã����ɣ����ؿ�����\n\n" NOR,
                       ob, me);    
        if ( ! ob->is_busy() ) 
        {
            ob->exert_function("powerup"); 
            ob->exert_function("shield");
        }
        me->competition_with(ob);
        return 1;
}
int accept_object(object me, object ob)
{             
        int i, ii;
        object jy, *users, master;       
        
        jy = this_object();       
        
        if (ob->query("money_id") && ob->value() >= 500000)
        {    

            if ( me->query("combat_exp") < 1000000 )
            {
                command("say ��㾭��Ҳ������̨���׳��˰ɣ�");
                return 0;
            }       
            for(i = 1; i < 6; i++)
           {
                master = new("/u/sanben/leitai/npc" + i);
                master->restore();
                set("idlist/" + i, master->query("id"));
                set("namelist/" + i, master->query("name"));        
                destruct(master);
            }
     
            if ( me->query("id") == query("idlist/5") )
            {
                command("say �ϴ����Ѿ��������ˣ����Լ����Լ�����");
                return 0;
            }

            users = users();
            for(i=0;i<sizeof(users);i++)
            {
                if ( users[i]->query_temp("leitai") 
                     && users[i]->query("id") == me->query("id") )
                { 
                   command("say �����ڲ������ڴ����𣬻�Ҫ����Ǯ��ʲô��");
                   return 0;            
                }
                if ( users[i]->query_temp("leitai") 
                     && users[i]->query("id") != me->query("id") )
                { 
                   command("say �����������ڴ��ޣ���ٵ������ɡ�");
                   return 0;            
                }

            }       

            command("say �ţ�������Ͱ�������ްɡ�����׼�����˾�����ready��");          
            

            me->set_temp("leitai/paid", 1);
            me->set_temp("leitai/prepare", 1);              
            
            me->set_temp("leitai/level",0);                    
 
            for( ii=1; ii < 6; ii++)
            {
               if ( query("idlist/" + ii ) == me->query("id") )
               {
                   me->set_temp("leitai/old_lvl",ii);
                   me->set_temp("leitai/level",ii);    
               }   
            }            
            destruct(ob);

            remove_call_out("remind");
            call_out("remind", 900, me);

            remove_call_out("end_all");
            call_out("end_all", 1200, me);
            return 1;
       } else
       {
            command("say ����һ����ʮ���ƽ𣬲����ۣ�");
            return 0;
       }        
}

int do_no()
{
        command("say " + this_player()->name() + "��������Ŀ���������˲���֮�£�");
        return 1;
}

int do_no1()
{
    if ( !wizardp(this_player()))
    { 
        command("say " + this_player()->name() + "�����ﲻ�ܸ�����¡�");
        return 1;
    }
    return 0;
}

int do_ready()
{
    object me;
    me = this_player();
    if (! me->query_temp("leitai/prepare") ) return 0;

    me->delete_temp("leitai/prepare");
    call_other(__FILE__, "get_npc_out", (me->query_temp("leitai/level") + 1) );  
    return 1;
}

void remind(object me)
{
    if ( me ) 
       tell_object(me, HIG"��ע�⣬��Ĵ���ʱ�仹ʣʮ���ӡ�\n"NOR);
}

void end_all(object me)
{    
    
    if ( me ) 
    {
       tell_object(me, HIG"�ܱ�Ǹ����Ĵ���ʱ���Ѿ������ˡ�\n"NOR);
       me->delete_temp("leitai");
    }      
       
}


int get_npc_out(int level)
{
     object npc, me;
     string msg;

     me = this_player();
        
     if ( level > 5 ) level = 5;
     npc = new(__DIR__"npc" + level);   
     npc->set("qi", npc->query("max_qi"));  
     npc->set("eff_qi", npc->query("max_qi"));  
     npc->set("jing", npc->query("max_jing"));  
     npc->set("eff_jing", npc->query("max_jing")); 
     npc->set("neili", npc->query("max_neili"));  
     npc->set("born_time", time());
  
     if (npc) npc->move(LEITAI);  
     
     msg = "��������������¥����������ھ�����̨��ս����"
                  "\n            �����"NOR HIR+
                  me->name() + "(" + me->query("id") + ")" + NOR HIY 
                 "��ս"NOR + npc->query("nickname") + NOR HIG + npc->name() + 
                 "(" + npc->query("id") + ")"NOR + 
                 HIY"��������\n            ��ӭ���ǰ���ۿ���\n\n"NOR;
     call_other(__FILE__, "shout_message", msg);

     message_vision(HIW"\nֻ�����������һ�ӣ�$N���Ҵҵ���������̨��׼��Ӧս��\n\n"NOR, npc); 
     message_vision(HIC"$N��$n˵�����²��˳٣�������Ϳ�ʼ���԰ɡ�\n\n"NOR, npc, me); 
     return 1;
}

void set_tishen(object winner)
{   
    int lvl;        
    lvl = winner->query_temp("leitai/level");
    winner->set_temp("leitai/set_start", 1);
    
    tell_room(LEITAI, HIC"\n��ӹ˵����������������ϲ"NOR HIR+ winner->name() +
                             NOR HIC"����������֮�С�\n\n"NOR);
 
    tell_object(winner, HIW"�������������ʾΪ�Լ��������������ã��������£�\n"NOR 
                HIG"��������������ʲô�����ĸ�ʽΪsetwp ��������\n"NOR
                HIC"�ɹ�ѡ��ı����У�\n"
                "�����������ޡ����ơ��｣��������������ָ�ס��ȡ�\n"NOR                 
                HIY"���������������еĸ�ʽΪsetpfm ��������|��������|��������\n"
                "�磺setpfm taixuan-gong|unarmed|xuan��\n"NOR 
                HIR"����Ϊ���������������С�\n"
                "������ʱ�����ƣ��뾡�죡\n"NOR);
}

void shout_message(string msg)
{
        message("channel:chat", HIY "�����ֿ챨����ӹ[Jin Yong]��" + msg + "\n" NOR,
                all_interactive());
}

void unconcious()
{
        revive();
        set("eff_qi", query("max_qi"));
        set("qi", query("max_qi"));
        set("eff_jing", query("max_jing"));
        set("jing", query("max_jing"));
        set("jingli", query("eff_jingli"));
        remove_all_enemy(1);
}
void die()
{
        unconcious();
}


