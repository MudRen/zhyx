/************************�л�ת��ϵͳ�����ļ�*********************************
created by yuchang for ZHYX
*******************************************************************************/

// #pragma optimize
// #pragma save_binary

inherit F_DBASE;

#include <ansi.h>
#include <localtime.h>

#define MEMBER_D                        "/adm/daemons/memberd"

int change_data(object me, string specials);

mapping special2 = ([
       "zhuha"      :   "�����Ե",
       "yuan"       :   "��Ԫ��",
       "jin"        :   "��ħ����",
       "tong"       :   "ͨ������",
       "bian"       :   "�����ѧ",
       "guimai"     :   "��������",
       "xunying"    :   "��Ӱ����",
       "wushuang"   :   "��ʿ��˫",
       "zhushang"   :   "����֮��",
       "jinghua"    :   "��������",
       "dian"       :   "��ʯ�ɽ�",
]);

mixed get_all_specials()
{
        return special2;
}

string get_special_name(string arg)
{
        return special2[arg];
}
/**************************************************************************
 ����ת�����ݣ��Ƿ����������ʮ������
***************************************************************************/
int check_data(object me)
{
       if (wizardp(me))return 1;

       if (me->query("scborn/ok"))
       {
              write("���Ѿ�ת�����ˣ�\n");
              return 0;
       }
       if (! ultrap(me))
       {
              write("�㻹û�г�Ϊ��ѧ����ʦ��\n");
              return 0;
       }
       if (! me->query("breakup"))
       {
              write("�㻹û�д�ͨ�ζ�������\n");
              return 0;
       }
       if (! me->query("animaout"))
       {
              write("�㻹û������ԪӤ������\n");
              return 0;
       }
       if (! me->query("death"))
       {
              write("�㻹û�д�ͨ�������أ�\n");
              return 0;
       }
       if (me->query("league"))
       {
              write("��Ȼ��Խ����������������Ǿ;������ͬ�˵���ʿ�Ǹ��ɣ�\n");
              write(HIR "����������������ͬ�ˣ�\n" NOR);

              return 0;
       }

       return 1;
}
/***************************************************************************
 ����ת�����ݣ��Ƿ����ת������
     1����Ϊ��ѧ����ʦ
     2������ʮ�������
     3����ͨ�������أ�ԪӤ�������ζ�����
***************************************************************************/
int check_data2(object me)
{
       if (wizardp(me))return 1;

       if (me->query("scborn/ok"))
       {
              write("���Ѿ�ת�����ˣ�\n");
              return 0;
       }
       if (! ultrap(me))
       {
              write("�㻹û�г�Ϊ��ѧ����ʦ��\n");
              return 0;
       }
       if (! me->query("breakup"))
       {
              write("�㻹û�д�ͨԪӤ������\n");
              return 0;
       }
       if (! me->query("animaout"))
       {
              write("�㻹û������ԪӤ������\n");
              return 0;
       }
       if (! me->query("death"))
       {
              write("�㻹û�д�ͨ�������أ�\n");
              return 0;
       }
       if (me->query("sky12/floor") != 13)
       {
              write("�㻹û��ͨ��ʮ�������Ŀ��飡\n");
              return 0;
       }

       return 1;
}


/**************************************************************************
 ��ʼת��
 ��ʼ��һЩת����������ݣ�Ȼ���������
**************************************************************************/
int start_scborn(object me)
{
       string *specials;
       string spe, user, login;

       specials = keys(special2);

       user =  me->query("id");
       login = user;
       user = "/data/user/" + user[0..0] + "/" + user + ".o";
       login = "/data/login/" + user[0..0] + "/" + user + ".o";

       // ��������
       mkdir("/data/scborn/" + user);
       cp(user, "/data/scborn/" + me->query("id") + ".u"); // user.o
       cp(user, "/data/scborn/" + me->query("id") + ".l"); // login.o

       // ���ѡȡһ��ת������
       while(1)
       {
               spe = specials[random(sizeof(specials))];
               if (spe == "wushuang")continue;

               break;
       }

       // ��������
       if (MEMBER_D->is_valib_member(me->query("id")))return change_data(me, spe);

       else return change_data(me, 0);

}

/**************************************************************************
 �������ݡ�
 ������Ҫת��ǰ�����ݣ��������������
**************************************************************************/
int change_data(object me, string specials)
{
       int i;
       mixed sdata, klist, newdata;
       mapping special_sk, skills, old_sk;

       if (! me)me = this_player();

       sdata = me->query_entire_dbase();

       if (! sdata)return 0;

       klist = keys(sdata);

       // ����������ת������Ȼ������
       newdata = ([]);

       newdata += ([ "sec_id"      :   me->query("sec_id")]);
       newdata += ([ "cwf"         :   me->query("cwf") ]);
       newdata += ([ "env"         :   me->query("env") ]);
       newdata += ([ "pmskills"    :   me->query("pmskills") ]);
       newdata += ([ "unit"        :   me->query("unit") ]);
       newdata += ([ "libs"        :   me->query("libs") ]);
       newdata += ([ "startroom"   :   me->query("startroom") ]);
       newdata += ([ "can_speak"   :   me->query("can_speak") ]);
       newdata += ([ "member"      :   me->query("member") ]);
       newdata += ([ "kar"         :   me->query("kar") ]);
       newdata += ([ "last_save"   :   me->query("last_save") ]);
       newdata += ([ "channels"    :   me->query("channels") ]);
       newdata += ([ "schedule"    :   me->query("schedule") ]);
       newdata += ([ "last_read_news"  :   me->query("last_read_news") ]);
       newdata += ([ "email"       :   me->query("email") ]);
       newdata += ([ "born"        :   me->query("born") ]);
       newdata += ([ "birthday"    :   time() ]);
       newdata += ([ "startroom"   :   me->query("startroom") ]);
       newdata += ([ "can_summon"  :   me->query("can_summon") ]);
       newdata += ([ "attitude"    :   me->query("attitude") ]);
       newdata += ([ "character"   :   "��ʿ��˫" ]);
       newdata += ([ "id"          :   me->query("id") ]);
       newdata += ([ "message"     :   me->query("message") ]);
       newdata += ([ "registered"  :   me->query("registered") ]);
       newdata += ([ "per"         :   me->query("per") ]);
       newdata += ([ "race"        :   me->query("race") ]);
       newdata += ([ "cwd"         :   me->query("cwd") ]);
       newdata += ([ "purename"    :   me->query("purename") ]);
       newdata += ([ "surname"     :   me->query("surname") ]);
       newdata += ([ "name"        :   me->query("name") ]);
       newdata += ([ "balance"     :   me->query("balance") ]);
       newdata += ([ "gender"      :   me->query("gender") == "����" ? "����" : me->query("gender") ]);
       newdata += ([ "type"        :   me->query("type") ]);
       newdata += ([ "board_last_read":me->query("board_last_read") ]);

       // ��Ҫ�������õ�����
       newdata += ([ "age"         :   5 ]); // ת����Ϊ5��
       newdata += ([ "mud_age"     :   0 ]);
       newdata += ([ "born_family" :   "û��" ]);
       newdata += ([ "eff_jing"    :   100 ]);
       newdata += ([ "eff_qi"      :   100 ]);
       newdata += ([ "max_jingli"  :   0 ]);
       newdata += ([ "jingli"      :   0 ]);
       newdata += ([ "food"        :   200 ]);
       newdata += ([ "water"       :   200 ]);
       newdata += ([ "jing"        :   100 ]);
       newdata += ([ "max_jing"    :   100 ]);
       newdata += ([ "max_qi"      :   100 ]);
       newdata += ([ "max_neili"   :   0 ]);
       newdata += ([ "neili"       :   0 ]);
       newdata += ([ "potential"   :   999 ]);
       newdata += ([ "qi"          :   100 ]);
       newdata += ([ "shen"        :   0 ]);
       newdata += ([ "shen_type"   :   0 ]);
       newdata += ([ "title"       :   "��ͨ����" ]);
       // �츳
       newdata += ([ "str"         :   me->query("str") ]);
       newdata += ([ "con"         :   me->query("con") ]);
       newdata += ([ "int"         :   me->query("int") ]);
       newdata += ([ "dex"         :   me->query("dex") ]);
       newdata += ([ "per"         :   30 ]);


       // ���ü���
       skills = ([]);
       skills += ([ "martial-cognize"     :    300 ]);

       // �����Դ��书���豣����ʮ��
       if (stringp(me->query("pmskills/skid")))
       {
              skills += ([ me->query("pmskills/types")     :    30 ]);
              skills += ([ me->query("pmskills/skid")      :    30 ]);
       }

       // ���ת��ǰ������
       for (i = 0; i < sizeof(klist); i ++)
       {
               me->delete(klist[i]);
       }

       old_sk = me->query_skills();
       klist = keys(old_sk);
       for (i = 0; i < sizeof(klist); i ++)
       {
               me->delete_skill(klist[i]);
       }

       // ����������
       klist = 0;
       klist = keys(newdata);
       for (i = 0; i < sizeof(klist); i ++)
       {
               me->set(klist[i], newdata[klist[i]]);
       }

       klist = 0;
       klist = keys(skills);
       for (i = 0; i < sizeof(klist); i ++)
       {
               me->set_skill(klist[i], skills[klist[i]]);
       }

       // �������⼼��
       me->set("special_skill/wushuang", 1); // ��ʿ��˫

       if (MEMBER_D->is_valib_member(me->query("id")) && stringp(specials))
              me->set("special_skill/" + specials, 1);

       if (specials == "bian") // �����ѧ
              me->set_skill("literate", 300);

       if (specials == "jinhua") // ��������
       {
              me->add("int", 2);
              me->add("con", 2);
              me->add("dex", 2);
              me->add("str", 2);
       }
       if (specials == "xunying") // ��Ӱ����
       {
              me->set_skill("mathematics", 300);
              me->set_skill("count", 300);
       }

       // ת����־����
       me->set("scborn/ok", 1);

       me->save();

       log_file("static/scborn", sprintf("%s(%s) scborn at %s",
                                 me->name(),
                                 me->query("id"),
                                 ctime(time())));

       return 1;
}
