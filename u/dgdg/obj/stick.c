//����:ħ����---Ϲ����ר��ħ������   ����:Ϲ����
//����Ŀ��:1.��һ����Ϥlpc   2.���Լ����ӹ��ܷ������
//���д���Ʒ��������call ��clone��summon��smash��dest�ȹ���
//����ƷΪΨһ������Ʒ������Ϲ��������ʹ��

#include <ansi.h>
#include <weapon.h>

inherit XSWORD;
int is_weapon() {return 1;}

void create()
{
        set_name(HIG "������ר��ħ����" NOR, ({ "magic stick", "stick"}));
        if (clonep())
                  set_default_object(__FILE__); 
        else {
                set("long", HIG "ħ����---������ר��ħ�����ߣ�\n" +
                                     "   һ�����֣����²��\n" + 
                                     HIB"��Ҫָ��:\n" + "bian(��)��shuju(��������)��" +
                                        "jineng������)��linshi(��ʱ����)��shezhi(���õȼ�)��\n" +
                                     "bring(ץ������)��bianmei(��û)��sha(ɱ)��qsha(ȫɱ)��ding(����)\n"NOR);
                set("unit", "��");
                set("value", 10000);
                set("weight", 3000);
                set("material", "tian jing");
                set("owner_id","dgdg");
                set("no_get",1);
                set("no_beg",1);
                set("no_steal",1);
                set("wield_msg",HIC"�����������ģ�Сղ��Ů����С���ڽ�ɽһ�ҷ����н��ϰࡣǰ�����ϻؼң�С��˵���︺���˶������¹棬�ϰ�ٵ����ˣ�Ҫ��ͬ�������ӵ���Ϸ������Ҫ���ܡ��ͷ������ͷ����������Գš���������ݡ��ͷ������������˶������ֻ�ܽ��ܡ�����˵�Ѿ����˱��������ˡ�������Ů���ѳԿ���Сղŭ�����գ���������ô�ף�˭��˭����Ů����û˵�����Ҿ��û���̫���ˡ���Сղ�������ֹ涨��ȫ����ɧ�ţ�ϣ��Ů�Ѵ�ְ����С��ȴ���ϣ���Ϊ��涨ûʲô���á�˫�����ּ�����Ϊ�˻�����һ�ܡ�������Ϊ���ֹ涨�ܲ������о���Ů��������Ҫ�����͡����������磬����С��Сղ�µ�968111˵����������һ���������������飬Ϊ��������Ů���Ѵ�һ�ܡ������̱�Ѷ ˵����ݣ��ܶ��˻����뵽ͯ�꣬����93��Ŀ���ү���������ݿɲ�ֻ���ں��ӣ������Լ������������Ҫ����顱����ס��ɿڵĿ���ү�����ݺ������ݡ���Ե�������Լ����������˷��ݡ�30�������������ϰ�һ���þ���ɡ�����ϴ���������������200������ݡ�����˵����ÿ�춼Ҫ��������ȥ�ŷ��ݣ������������壬�����ж��ѹ��ϰ��˼���ϣ����һ�죬200���������һ������족��

������������200�������
\n"NOR); 
                set("unwield_msg",HIC"�����������ģ�Сղ��Ů����С���ڽ�ɽһ�ҷ����н��ϰࡣǰ�����ϻؼң�С��˵���︺���˶������¹棬�ϰ�ٵ����ˣ�Ҫ��ͬ�������ӵ���Ϸ������Ҫ���ܡ��ͷ������ͷ����������Գš���������ݡ��ͷ������������˶������ֻ�ܽ��ܡ�����˵�Ѿ����˱��������ˡ�������Ů���ѳԿ���Сղŭ�����գ���������ô�ף�˭��˭����Ů����û˵�����Ҿ��û���̫���ˡ���Сղ�������ֹ涨��ȫ����ɧ�ţ�ϣ��Ů�Ѵ�ְ����С��ȴ���ϣ���Ϊ��涨ûʲô���á�˫�����ּ�����Ϊ�˻�����һ�ܡ�������Ϊ���ֹ涨�ܲ������о���Ů��������Ҫ�����͡����������磬����С��Сղ�µ�968111˵����������һ���������������飬Ϊ��������Ů���Ѵ�һ�ܡ������̱�Ѷ ˵����ݣ��ܶ��˻����뵽ͯ�꣬����93��Ŀ���ү���������ݿɲ�ֻ���ں��ӣ������Լ������������Ҫ����顱����ס��ɿڵĿ���ү�����ݺ������ݡ���Ե�������Լ����������˷��ݡ�30�������������ϰ�һ���þ���ɡ�����ϴ���������������200������ݡ�����˵����ÿ�춼Ҫ��������ȥ�ŷ��ݣ������������壬�����ж��ѹ��ϰ��˼���ϣ����һ�죬200���������һ������족��

������������200�������
\n"NOR);                             
             }
         init_xsword(9000);       
        setup();
}

void init()
        {       
                


                if (environment(this_object())->query("id") != "dgdg")
                {    
                     message("vision", HIY + "ħ���Ⱥ�Ȼ�ѵ�һ�������ˣ�"
                        "�����ȥѰ����������ȥ�˰ɡ�\n" NOR,
                            environment(this_object()));

                     if (! find_player("dgdg")) 
                     {                        
                            destruct(this_object());
                     }
                    else
                     { 
                            this_object()->move(find_player("dgdg"));
                            tell_object(find_player("dgdg"), 
                                HIC"ħ���Ⱥ�Ȼ�ɵ��������\n"NOR);
                     }
                }
                add_action("do_bian","bian");
                add_action("do_shuju","shuju");
                add_action("do_jineng","jineng");
                add_action("do_linshi","linshi");
                add_action("do_shezhi","shezhi");
                add_action("do_bring","bring");
                add_action("do_bianmei","bianmei");
                add_action("do_sha","sha");
                add_action("do_qsha","qsha");
                add_action("do_ding","ding");
        }

// clone���   ָ��bian
int do_bian(string arg)

        {       
                object mm;
                
                if (this_player()->query("id") != "dgdg")
                return notify_fail("���ħ����ֻ������������ʹ����\n");
                
                mm=new(arg);
                if (! clonep(mm)) 
                {write("���������ն�����䲻����ѽ��\n");return 1;}
                else
                {
                mm->move(this_player());
                message_vision(HIW"$NĬ���������ħ�������һָ�������ỽһ�����䡱��\n��ʱ��"NOR + 
                                mm->query("name") + HIW"���˳�����\n"NOR, this_player());         
                }
                return 1;
        }
//ѡ��������������   ָ��shuju
int do_shuju(string data)

        {       if (data == 0)
                return notify_fail("����ı��Լ���ʲô����?\n");
                this_player()->set_temp("shuju", data);
                write("������Լ���" + data + "����(shezhi)�ɶ�����ֵ�أ�\n");
                return 1;
        }

//ѡ�����ü��ܵȼ�  ָ��jineng
int do_jineng(string skill)

        {       if (skill == 0)
                return notify_fail("����ı��Լ���ʲô����?\n");
                this_player()->set_temp("jineng", skill);
                write("������Լ���" + skill + "��������(shezhi)�ɶ��ټ��أ�\n");
                return 1;
        }
//ѡ��������ʱ����   ָ��linshi
int do_linshi(string temp)

        {       if (temp == 0)
                return notify_fail("����ı��Լ���ʲô" + YEL"��ʱ" + NOR"����?\n");
                this_player()->set_temp("linshi", temp);
                write("������Լ�����ʱ����" + temp + "����(shezhi)��ʲô�أ�\n");
                return 1;
        }


//������ѡ����Ŀ��������  ָ��shezhi
int do_shezhi(string level)

        {       object me;
                int lev;
                me = this_player();
                lev = atoi(level);      

                if (this_player()->query("id") != "dgdg")
                return notify_fail("���ħ����ֻ������������ʹ����\n");
                
                if (! me->query_temp("shuju") && ! me->query_temp("jineng")
                        && ! me->query_temp("linshi") )
                return notify_fail("������shuju��jineng��linshiָ����Ҫ���õ���Ŀ��\n");
                                
                if (me->query_temp("shuju")) 
                {                       
                    me->set(me->query_temp("shuju"), lev);

                    message_vision(HIW"$NĬ���������ħ���ȶ�ס�Լ�һָ�������ỽһ�����䡱��\n" + 
                                HIM"�漣������!\n"NOR, this_player());          
                    
                    write("ħ���Ƚ���"HIC + me->query_temp("shuju") +
                         NOR"�����ó���"HIG + lev + NOR"\n");

                    me->delete_temp("shuju");
                    me->delete_temp("jineng");
                    me->delete_temp("linshi");
                    return 1;
                }

                if (me->query_temp("jineng")) 
                {       
                    me->set_skill(me->query_temp("jineng"), lev);

                     message_vision(HIW"$NĬ���������ħ���ȶ�ס�Լ�һָ�������ỽһ�����䡱��\n" + 
                                HIM"�漣������!\n"NOR, this_player());             
                        
                    write("ħ���Ƚ����"HIY + me->query_temp("jineng") +
                         NOR"��������ó���"HIW + lev + NOR"����\n");

                    me->delete_temp("shuju");
                    me->delete_temp("jineng");
                    me->delete_temp("linshi");
                    return 1;
                }

if (me->query_temp("linshi")) 
                {                       
                    me->set_temp(me->query_temp("linshi"), lev);

                    message_vision(HIW"$NĬ���������ħ���ȶ�ס�Լ�һָ�������ỽһ�����䡱��\n" + 
                                HIM"�漣������!\n"NOR, this_player());          
                    
                    write("ħ���Ƚ������ʱ����"HIC + me->query_temp("linshi") +
                         NOR"���ó���"HIG + lev + NOR"\n");

                    me->delete_temp("shuju");
                    me->delete_temp("jineng");
                    me->delete_temp("linshi");
                    return 1;
                }
        }

//ץ������  ָ��bring
int do_bring(string arg)

        {       object me, ob; 
                me = this_player();
                
                if (me->query("id") != "dgdg")
                return notify_fail("���ħ����ֻ������������ʹ����\n");

                if (! arg)
                return notify_fail("��Ҫץ�ĸ��������?\n");

                if (find_living(arg) == 0)
                return notify_fail("�Ҳ����������,û��ץ������!\n");

                ob = find_living(arg);          
                if (environment(ob) == environment(me) ) 
                return notify_fail("�ף���һ�����������ǰѽ��\n");
                message("vision", HIM"ֻ�����Ʈ��һ����ɫ���ƣ�\n" +
                                ob->query("name") + "һ��������������ת�۷ɵ���Ӱ���١�\n"NOR,
                                environment(ob), ({ob}));               

                message_vision(HIW"ֻ��$NĬ������ỽһ������������\n" +
                             find_living(arg)->query("name") +
                                 HIG"ͻȻ�����˳�����\n"NOR, me);

                tell_object(find_living(arg), HIM"ֻ�����Ʈ��һ����ɫ���ƣ�\n"+
                                         "���������ƣ��ɰ��ɰ���һ�¾ͷɵ���" +
                                           me->query("name") + "��ǰ��\n"NOR);
                
                find_living(arg)->move(environment(me));                
                return 1;
        }

//�������(��Ҳ�������) ָ��bianmei

int do_bianmei(string ob)
        {       
                int i;
                object *all;
                
                if (this_player()->query("id") != "dgdg")
                return notify_fail("���ħ����ֻ������������ʹ����\n");

                if (! ob) 
                return notify_fail("��Ҫ��ʲô��ûѽ��\n");

                if (find_player(ob)) 
                return notify_fail("����ұ�û�������̫�ðɣ���\n");

                all = all_inventory(environment(this_player()));
                 for(i = 0; i < sizeof(all); i++) 
                {
                        if ( ob ==all[i]->query("id") ) 
                        {       
                                message_vision(YEL"ֻ��$NĬ���������ħ���ȶ�ס"NOR + all[i]->query("name") + 
                                                YEL"һָ�������ỽһ����ȥ!��\n"NOR +
                           all[i]->query("name") + YEL"��ʱ��ʧ����Ӱ���١�\n"NOR, this_player());
                            
                               destruct(all[i]);return 1;
                        }                       
                }
                write("�������û�������������ô������ûѽ!\n");
                return 1;       
        }

//ɱ��ָ��npc(�������Ч)  ָ��sha
int do_sha(string ob)
        {               
                int i;
                object *all;
                
                if (this_player()->query("id") != "dgdg")
                return notify_fail("���ħ����ֻ������������ʹ����\n");

                if (! ob) 
                return notify_fail("��Ҫ���ĸ�npcɱ��ѽ��\n");

                if (find_player(ob)) 
                return notify_fail("Ҫɱ��ң������̫�ðɣ���\n");                     
                
                all = all_inventory(environment(this_player()));
                 for(i = 0; i < sizeof(all); i++) 
                {
                        if ( ob ==all[i]->query("id") ) 
                        {       
                                if ( ! living(all[i]) )
                                return notify_fail("�Ƕ����ֲ��ǻ����ôɱ��ѽ����\n");
                
                                message_vision(YEL"ֻ��$NĬ���������ħ���ȶ�ס"NOR + all[i]->query("name") + 
                                                YEL"һָ�����Ŵ��һ����ȥ����.......��\n" +
                                HIR"ħ����ͻȻ���һ�����磬˲�佫" NOR +
                           all[i]->query("name") + HIR"��Ϊ�˻ҽ���\n"NOR, this_player());
                                
                               all[i]->die();
                                return 1;
                        }                       
                }
                write("�������û�����npc����ô����ɱ��ѽ!\n");
                return 1;
        }

//ɱ��һ������������npc(�������Ч)  ָ��qsha
int do_qsha()
        {               
                int i;
                object *all;
                
                if (this_player()->query("id") != "dgdg")
                return notify_fail("���ħ����ֻ������������ʹ����\n");                                
                
                all = all_inventory(environment(this_player()));
                
                message_vision(YEL"ֻ��$NĬ���������ħ���ȶ�ס����һָ\n" + 
                                                "���Ŵ��һ����:��������ȥ����.......��\n" +
                                                HIR"ħ����ͻȻ������������磬˲�佫�����" +
                                                "���л��ﶼ��Ϊ�˻ҽ���\n" +
                                                "���Ǳ�ԭ�ӵ�������Ӵ��\n\n"NOR, 
                                                this_player());

                 for(i = 0; i < sizeof(all); i++) 
                {
                        if ( find_player(all[i]->query("id")) && all[i]->query("id") != "dgdg" )
                        {
                            message_vision(HIY"$N�ŵ�ֱ���£�" + 
                                                "�ҿ��صÿ�Ŷ��һ�١�\n"NOR, 
                                                all[i]);
                        }
                        if ( living(all[i]) && ! find_player(all[i]->query("id")) )
                        {                                               
                        all[i]->die();                  
                        }       
                }               
                return 1;
        }

//����  ָ��ding
int do_ding(string ob)
        {               
                int i;
                object *all;
                
                if (this_player()->query("id") != "dgdg")
                return notify_fail("���ħ����ֻ������������ʹ����\n");

                if (! ob) 
                return notify_fail("��Ҫ��˭��סѽ��\n");                                       
                
                all = all_inventory(environment(this_player()));
                 for(i = 0; i < sizeof(all); i++) 
                {
                        if ( ob ==all[i]->query("id") ) 
                        {       
                                if ( ! living(all[i]) )
                                return notify_fail("�Ƕ��������Ͳ��ᶯ����ʲô������\n");
                
                                message_vision(HIW"ֻ��$NĬ���������ħ���ȶ�ס"NOR + all[i]->query("name") + 
                                                HIW"һָ�����Ŵ��һ������.......��\n" +
                                HIR"ħ����ͻȻ���һ������" NOR +
                           all[i]->query("name") + HIR"��ʱ��������ԭ�ض������ã�\n"NOR, this_player());
                                
                               all[i]->start_busy(300);
                                return 1;
                        }                       
                }
                write("�������û������ˣ���ô������סѽ!\n");
                return 1;
        }
// ������Ʒ
int receive_summon(object me)
{
	return ITEM_D->receive_summon(me, this_object());
}

// ������Ʒ
int hide_anywhere(object me)
{     
      object item = this_object();

      if (me->query("jingli") < 100)
        {
                tell_object(me, "����ͼ��" + item->name() +
                            "��ȥ�����Ǿ������ã����Է�������������\n");
                return 0;
        }
        me->add("jingli", -100);

        message_vision(HIM "$N" HIM "����һ��" + item->name() +
                       HIM "����Ȼ�����ټ���\n", me);
        destruct(item);
        return 1;
}

// ���ڵ���
int do_stab(object me)
{
        return ITEM_D->do_stab(me, this_object());
}


int query_autoload() 
     { return 1; } 
