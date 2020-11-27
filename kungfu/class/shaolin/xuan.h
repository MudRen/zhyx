// xuan.h for fight and get letter from Xuan

#include "shaolin.h"

int accept_object(object ob, object obj)
{
        object me = this_object();

#if IS_XUAN_CI
        int r;

        if (r = ::accept_object(ob, obj))
                return r;
#endif

        if (obj->query("id") == "tuijian xin4" &&
            ob->query_temp("have_letter"))
        {
                ob->set_temp("apprentice_ok",1);
                command("say �ã�" + ob->query("name") +
                        "����Ը�����Ϊʦ��");
                destruct(obj);
                return 1;
        }

        command("smile");
        command("say �ⶫ�����ҿ�û��ʲ���á�");
        command("give " + obj->query("id") + " to " + me->query("id"));
        return 0;
}

void attempt_apprentice(object ob)
{
        object me  = this_object();
        mapping ob_fam;
        mapping my_fam  = me->query("family");

        string name, new_name;

        if (! permit_recruit(ob))
                return;

        if (! (ob_fam = ob->query("family")) ||
            ob_fam["family_name"] != "������")
        {
                command("say " + RANK_D->query_respect(ob) +
                        "�뱾��������������֪�˻��Ӻ�̸��");
                return;
        }

        if ((string)ob->query("class") != "bonze" &&
            ob_fam["family_name"] == "������") 
        {
                command("say " + RANK_D->query_respect(ob) +
                        "���׼ҵ��ӣ�����������ѧ�ա�");
                return;
        }

        if (ob_fam["generation"] <= my_fam["generation"])
        {
                command("say " + RANK_D->query_respect(ob) +
                        "��ƶɮ����ҵ� !");
                return;
        }

        if (ob_fam["generation"] == (my_fam["generation"] + 1))
        {
                command("say " + ob_fam["master_name"] +
                        "��ͽ�������ܵ���������ˣ������� !");
                command("recruit " + ob->query("id"));
        }

        if (ob_fam["generation"] == (my_fam["generation"] + 2))
        {
                if (ob->query_temp("apprentice_ok") ||
                    ob->query("luohan_winner"))
                {
                        ob->delete_temp("have_letter");
                        ob->delete_temp("apprentice_ok");
        
                        command("say ��" + ob_fam["master_name"] +
                                "���������ҵİɣ���������");
                        command("say ƶɮ�ֵ�һ����֮�ţ����ǿ�ϲ�ɺأ�");

                        name = ob->query("name");
                        new_name = "��" + name[2..3];
                        ob->set("name", new_name);

                        command("say �ӽ��Ժ���ķ�������" + new_name +
                                "����ϲ������Ϊ�����ɳ��ֱ����ӣ�");
                        command("recruit " + ob->query("id"));
                } else
                {
                        command("say " + RANK_D->query_respect(ob) +
                                "���㼴û���Ƽ��ţ�Ҳû�й��޺���"
                                "����Խ����ʦ��");
                        return;
                }
        }

        return;
}

int accept_ask(object me, string topic)  
{
        switch (topic)  
        {        
        
        case "����" :
        case "����" :
        case "����" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;
        case "���ƾ�" :  
                return MASTER_D->teach_pfm(me, this_object(),  
                        ([ "perform" : "can_perform/dacheng-fosuo/chanrao",  
                           "name"    : "���ƾ�",  
                           "sk1"     : "dacheng-fosuo",  
                           "lv1"     : 80,  
                           "force"   : 100,  
                           "neili"   : 500,  
                           "gongxian": 100,  
                           "shen"    : 2000, ]));  
                break;  
        
        case "��ϼ����" :  
                return MASTER_D->teach_pfm(me, this_object(),  
                        ([ "perform" : "can_perform/yecha-gun/hongxia",  
                           "name"    : "��ϼ����",  
                           "sk1"     : "yecha-gun",  
                           "lv1"     : 120,  
                           "force"   : 150,  
                           "neili"   : 1000,  
                           "gongxian": 300,  
                           "shen"    : 5000, ]));  
                break;  
         
         case "��������" :  
                return MASTER_D->teach_pfm(me, this_object(),  
                        ([ "perform" : "can_perform/weituo-chu/jishi",  
                           "name"    : "��������",  
                           "sk1"     : "weituo-chu",  
                           "lv1"     : 120,  
                           "force"   : 180,  
                           "neili"   : 500,  
                           "gongxian": 300,  
                           "shen"    : 5000, ]));  
                break;  
         
         case "��������" :  
                return MASTER_D->teach_pfm(me, this_object(),  
                        ([ "perform" : "can_perform/longxing-jian/kong",  
                           "name"    : "��������",  
                           "sk1"     : "longxing-jian",  
                           "lv1"     : 160,  
                           "force"   : 250,  
                           "neili"   : 1500,  
                           "gongxian": 500,  
                           "shen"    : 10000, ]));  
                break;  
         
         case "���ָѨ" :  
                return MASTER_D->teach_pfm(me, this_object(),  
                        ([ "perform" : "can_perform/qufannao-zhi/lingkong",  
                           "name"    : "���ָѨ",  
                           "sk1"     : "qufannao-zhi",  
                           "lv1"     : 100,  
                           "force"   : 150,  
                           "neili"   : 1500,  
                           "gongxian": 500,  
                           "shen"    : 20000, ]));  
                break;  
         
         case "������" :  
                return MASTER_D->teach_pfm(me, this_object(),  
                        ([ "perform" : "can_perform/qinlong-shou/qin",  
                           "name"    : "������",  
                           "sk1"     : "qinlong-shou",  
                           "lv1"     : 100,  
                           "force"   : 120,  
                           "neili"   : 1000,  
                           "gongxian": 200,  
                           "shen"    : 20000, ]));  
                break;  
         
         case "��Ӱ����" :  
                return MASTER_D->teach_pfm(me, this_object(),  
                        ([ "perform" : "can_perform/ruying-suixingtui/ruying",  
                           "name"    : "��Ӱ����",  
                           "sk1"     : "ruying-suixingtui",  
                           "lv1"     : 160,  
                           "force"   : 250,  
                           "neili"   : 2000,  
                           "gongxian": 500,  
                           "shen"    : 50000, ]));  
                break;  
         case "һָ������" :  
                return MASTER_D->teach_pfm(me, this_object(),  
                        ([ "perform" : "can_perform/jingang-zhi/san",  
                           "name"    : "һָ������",  
                           "sk1"     : "jingang-zhi",  
                           "lv1"     : 200,  
                           "force"   : 300,  
                           "neili"   : 3000,  
                           "gongxian": 800,  
                           "shen"    : 50000, ]));  
                break;  
         
        case "��ʯ����" :  
                return MASTER_D->teach_pfm(me, this_object(),  
                        ([ "perform" : "can_perform/woshi-zhang/po",  
                           "name"    : "��ʯ����",  
                           "sk1"     : "woshi-zhang",  
                           "lv1"     : 120,  
                           "force"   : 140,  
                           "neili"   : 1000,  
                           "gongxian": 200,  
                           "shen"    : 20000, ]));  
                break;  
         
         case "�޺���ħ" :  
                return MASTER_D->teach_pfm(me, this_object(),  
                        ([ "perform" : "can_perform/luohan-gun/xiangmo",  
                           "name"    : "�޺���ħ",  
                           "sk1"     : "luohan-gun",  
                           "lv1"     : 80,  
                           "force"   : 100,  
                           "neili"   : 500,  
                           "gongxian": 100,  
                           "shen"    : 2000, ]));  
                break;  
         
         case "��Ѫצ" :  
                return MASTER_D->teach_pfm(me, this_object(),  
                        ([ "perform" : "can_perform/yingtuo-luozhua/xue",  
                           "name"    : "��Ѫצ",  
                           "sk1"     : "yingtuo-luozhua",  
                           "lv1"     : 200,  
                           "force"   : 300,  
                           "neili"   : 3000,  
                           "gongxian": 1000,  
                           "shen"    : 50000, ]));  
                break;  
         
         case "��������" :  
                return MASTER_D->teach_pfm(me, this_object(),  
                        ([ "perform" : "can_perform/liuhe-bian/lianhuan",  
                           "name"    : "��������",  
                           "sk1"     : "liuhe-bian",  
                           "lv1"     : 180, 
                           "sk2"     : "dodge",  
                           "lv2"     : 180,
                           "force"   : 270,  
                           "neili"   : 3000,  
                           "gongxian": 500,  
                           "shen"    : 50000, ]));  
                break;  
         
         case "�ȱ��־�" :  
                return MASTER_D->teach_pfm(me, this_object(),  
                        ([ "perform" : "can_perform/leiming-bian/cibei",  
                           "name"    : "�ȱ��־�",  
                           "sk1"     : "leiming-bian",  
                           "lv1"     : 160,
                           "sk2"     : "buddhism",  
                           "lv2"     : 150,  
                           "force"   : 250,  
                           "neili"   : 2000,  
                           "gongxian": 1000,  
                           "shen"    : 200000, ]));  
                break;  
                            
        default:  
                return 0;  
        }
}

