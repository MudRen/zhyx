#include <ansi.h>
inherit ITEM;
void create()
 {
    set_name("�֣ãĻ�", ({"vcd"}) );
    set_weight(1000);
    if( clonep() )
           set_default_object(__FILE__);
    else {
        set("unit", "̨");
        set("long", "һ̨�߼��ģ֣ãĻ������������ţ֣ã�Ƭ��\n");
         set("no_get",1);
         set("value",10000);
    }
    setup();
}

int init()
{
       add_action("do_play", "play");
        add_action("do_shut", "shut");
        add_action("do_kala", "kala");
        add_action("do_stop", "stop");
        return 1;       
}

int do_shut()
{
        if (this_object()->query_temp("play")==0) return notify_fail("����û�в��ţ֣ã�ѽ��\n");
        message_vision("$N��ң�ع��ˣ֣ãĻ���\n",this_player());
        this_object()->set_temp("play",0);
        remove_call_out("continue_play");
        return 1;
}

int do_play()
{
      // object ob;
        //ob=present("shi nv", environment(this_player())); 
//      if (objectp(ob)) {
                if (this_object()->query_temp("play")==1) return notify_fail("�������ڷ��ţ֣ã��ء�\n");
                if (this_object()->query_temp("kala")!=0) return notify_fail("���������˳������ϣ��ء�\n");
                this_object()->set_temp("play",1);
//              message_vision("$N�ߵ��֣ãĻ��ԣ�����һ�Ź���Ƭ�ŵ��֣ãĻ��С�\n",ob);
                call_out("start_play",2);
                return 1;
//      }
//      return 0;
}

int start_play()
{
        tell_room(environment(this_object()),"�����￪ʼ���ţ֣ãġ�\n");
        call_out("continue_play",1,-1); 
        return 1;       
}

int continue_play(int release)
{
        string *strs=({
                "\n\n                   "YEL"�󡡡���������������\n\n"NOR,"",
                "��  ��������գ�������������㱾����Ӧ�������滤����ʦ��������\n"
                "        ȥȡ���������Ȼ��ţħ����ͨ����Ҫ����ʦ������֪��֪��\n"
                "        �㷸��������\n",
                "����գ������£���׷����������ҹ����Ϊ����Ů���ҲŲ�ɱ�㣬��Ҫ\n"
                "        ��Ϊ���������ˣ�\n",
                "��  ɮ����գ�����ô����������������㽲���أ�\n",
                "��  �գ�������Ҫ����\n",
                "��  ɮ�����������ң�\n",
                "��  �����㲻��������ΪʲôҪ������ϼ�������������¹ⱦ�У��㲻\n"
                "        ������㿪����\n",
                "��  �գ���Ȼ�㲻��������͸����һ��ս��\n",
                "\n(��ս��¹ⱦ������һ�ף�����������ɮͷ�ϡ�)\n\n",
                "��  ɮ���ָ�ʲô��\n",
                "\n(������Ҫ���֣�ͻȻ����)\n\n",
                "��  ɮ��ιιι����Ҳ�Ҫ�����������᷸������ģ������Ҳ̫��Ƥ\n"
                "        �ˣ��Ҹ���˵�����㲻Ҫ���Ӷ���������ô�֡��㿴�һ�û˵\n"
                "        �����ְѹ��Ӹ��ӵ��ˣ��¹ⱦ���Ǳ��������ӵ�����Ⱦ\n"
                "        ������Ҫ���ҵ�С������ô�죿�����Ҳ���С�����ҵ���Щ��\n"
                "         ���ݲ�Ҳ�ǲ��Եģ�\n",
                "\n(���һ��ץס��ɮ���е��¹ⱦ��)\n\n",
                "��  ɮ����ʲô��\n",
                "��  �գ����֣�\n",
                "��  ɮ������Ҫ������գ���Ҫ����Ҫ�Ļ����˵����㲻˵����ô\n"
                "        ֪������Ҫ�أ���Ȼ����г���ؿ����ң������㻹��Ҫ����\n"
                "        ˵����Ҫ�ġ��������Ҫ���������ȥ�ɣ��㲻�������Ҫ\n"
                "        �ɣ��ѵ��������Ҫ�𣿡���\n",
                "��  �գ���Kao��\n"
                "\n(���һȭ����ɮ�򵹡�)\n\n",
                "��  ������������գ�\n"
                "��  �գ���ҿ�����������һ�û�¾ͳ�ƪ������������ߴߴ���ᣬ��\n"
                "        ����������һֻ��Ӭ���ˡ����Բ��𣬲���һֻ����һ�Ѳ�Ӭ\n"
             
                "\n(��յ��ط������쳣ʹ�ࡣ)\n\n",
                "��  �գ��������Ҿ�ץס��Ӭ�������Ķ�Ƥ�����ĳ��ӳ�������������\n"
                "        ������ס���Ĳ�������һ�����ǣ�����������ͷ�����������
\n"
                "        ���������仩���������������徻�ˡ����ڴ�����ף�Ϊʲ\n"
                "        ô��Ҫɱ����\n",
                "��  �����ߣ���գ�������ڣ�������Ͳ���ȥȡ������\n",
                "��  �գ�˵��ô���ʲô����ѽ��\n",
                "\n(����һ����������ձ��������������¶ƿ��)\n\n"
                "��  ����������Ҫ�����е���\n",
                "��  ɮ��ιιι��ͽ���д���ʦ����Ҳ�����Σ��������һ����·�ɣ�\n",
                "��  �����Ҳ���������û������ʴ�۽�����\n",
                "��  ɮ����������ʴ��˵һ����ƶɮԸ��һ����һ����(��ʮ���أ�\n"
                "        �����������һ��)�߼�����ӷ�\n"
                "\n(���Ƚ���ɮ������)\n\n",
        });
        if (release==0) {
                tell_room(environment(this_object()),"���ӷ����ˣ֣ãġ�\n");
                this_object()->set_temp("play",0);
                return 0;
        }
        if (release==-1) {
                continue_play(sizeof(strs));
                return 1;
        }
        tell_room(environment(this_object()),strs[sizeof(strs)-release]);
        call_out("continue_play",2,release-1);
        return 1;
}

int do_stop()
{
        if (this_object()->query_temp("kala")!=this_player()) return notify_fail("������û�г������ϣ�ѽ��\n");
        message_vision("$Nֹͣ�˳������ϣˡ�\n",this_player());
        this_object()->set_temp("kala",0);
        remove_call_out("continue_kala");
        return 1;
}

int do_kala()
{
  //     object ob;
        //ob=present("shi nv", environment(this_player())); 
        //if (objectp(ob)) {
                if (this_object()->query_temp("play")==1) return notify_fail("�������ڷ��ţ֣ã��ء�\n");
                if (this_object()->query_temp("kala")!=0) return notify_fail("���������˳������ϣ��ء�\n");
                this_object()->set_temp("kala",this_player());
//              message_vision("$N�ߵ��֣ãĻ��ԣ�����һ�ſ����ϣ��̷ŵ��֣ãĻ��У���$n�����˻�Ͳ��\n",ob,this_player());
                call_out("start_kala",2,this_player());
                return 1;
//      }
//      return 0;
}

int start_kala(object me)
{
        message_vision("$N��ʼ�������ϣˡ�\n",me);
        call_out("continue_kala",1,-1, me);     
        return 1;       
}

int continue_kala(int release, object me)
{
        string *strs=({
                "\n\n                   "YEL"��  ��  ��  ��  ��\n\n"NOR,
                CYN"$N��"+HIM+"���������ľ����뿪\n"NOR,
                CYN"$N: "+HIM+"Զ����Щ��ò����ı���\n"NOR,
                CYN"$N: "+HIM+"��������ȴ�������ǹػ�\n"NOR,
                CYN"$N: "+HIM+"�ſ���׷�������������\n"NOR,
                CYN"$N: "+HIM+"�Ǵ����㲻������뿪\n"NOR,
                CYN"$N: "+HIM+"��Ϊ������ò���ı���\n"NOR,
                CYN"$N: "+HIM+"���ǵ�Į�˷����޷��ٿ���\n"NOR,
                CYN"$N: "+HIM+"���������ż�į���ܹ���\n"NOR,
                CYN"$N: "+HIM+"������ӵ��������������ժ\n"NOR,
                CYN"$N: "+HIM+"��������סɲ����ԶΪ�㿪\n"NOR,
                CYN"$N: "+HIM+"������ӵ��������������ժ\n"NOR,
                CYN"$N: "+HIM+"��������סɲ����ԶΪ�㿪\n"NOR,
                CYN"$N: "+HIM+"�Ǵ����㲻������뿪\n"NOR,
                CYN"$N: "+HIM+"��Ϊ������ò���ı���\n"NOR,
                CYN"$N: "+HIM+"���ǵ�Į�˷���ֻΪ�㿪��\n"NOR,
                CYN"$N: "+HIM+"Ҫ����Զ���į��������\n"NOR,
                CYN"$N: "+HIM+"..............\n"NOR,
                
        });
        if (release==0) {
                message_vision("$N�����˿����ϣˡ�\n",me);
                this_object()->set_temp("kala",0);
                return 0;
        }
        if (release==-1) {
                continue_kala(sizeof(strs),me);
                return 1;
        }
        message_vision(strs[sizeof(strs)-release],me);
        call_out("continue_kala",2,release-1, me);
        return 1;
}

