//edit by smallfish 1998.07.16
// Smallfish@Huaxia

#include <ansi.h>
inherit F_CLEAN_UP;

int count3=0;
int if3();
int main(object me,string arg)
{
        object tempob,user_ob;
        string func,tilde,type;
        int val1,val2,i,j,ppl_cnt;
        string *dir, *ppls, tempid,tempname;
        mixed info;
        int info2,online;

        if (! SECURITY_D->valid_grant(me, "(arch)"))
                return 0;

        if (!arg)
                return notify_fail("��Ҫ��ʲô��\n");
        sscanf(arg,"%s %s %s %d %d",type,func,tilde,val1,val2);
        if (!type && type != "skill" && type != "setting")
                return notify_fail("������������help searchuser!\n");
        if ((!tilde)||((tilde!=">")&&(tilde!="<")&&(tilde!="=")&&(tilde!="<>")))
                return notify_fail("ƥ�����������help searchuser!\n");
        if (!val1)
                return notify_fail("ȱ�ٵ�һ����������help searchuser!\n");
        if ((!val2)&&(tilde=="<>"))
                return notify_fail("ȱ�ٵڶ�����!����help searchuser!\n");
        if ((val2<=val1)&&(tilde=="<>"))
                return notify_fail("��һ���ڶ��������ô���!����help searchuser!\n");
        message("system", "\n*** ���ڼ����Ҵ��浵�����������Ҫ������ʱ�䣬���Ժ�.... ***\n", users());

        seteuid(getuid());
        write("����У�\n");
        log_file("static/check_log", sprintf("-------------------------------------------------\n"));
        log_file("static/check_log", sprintf("����������[%s]%s%s%d,%d������嵥��\n",type,func,tilde,val1,val2));
        count3=0;
        ppl_cnt = 0;
        dir = get_dir(DATA_DIR + "login/");
        for(i=0; i<sizeof(dir); i++) {
                reset_eval_cost();
                write(dir[i]);
                ppls = get_dir(DATA_DIR + "login/" + dir[i] + "/",-1);
                ppl_cnt += sizeof(ppls);
                for(j=0; j<sizeof(ppls); j++) {
                        if( sscanf(ppls[j][0], "%s.o",tempid)==1 )
                     {
                                tempob=new(LOGIN_OB);
                                tempob->set("id",tempid);

                                if(!tempob->restore())
                           {
                                   destruct(tempob);
                                         write("û��" + tempid + "������!\n");
                                   continue;
                           }

                           if (tempob->query("id") != tempid)
                           {
                                   destruct(tempob);
                                   write("���"+tempid+"��ID"+tempob->query("id")+"����ȷ��\n");
                                   continue;
                           }

                           if (! objectp(user_ob = find_player(tempid)))
                           {
                                   online = 0;//����Ҳ�����
                                   user_ob = LOGIN_D->make_body(tempob);
                                   if (! user_ob)
                                   {
                                           destruct(tempob);
                                           write("�޷��������"+tempid+"��\n");
                                           continue;
                                   }

                                   if (! user_ob->restore())
                                   {
                                           destruct(tempob);
                                           destruct(user_ob);
                                           write("�޷���ȡ��ҵ���"+tempid+"��\n");
                                           continue;
                                   }
                           } else
                                   online = 1;

                           destruct(tempob);

                           tempid = user_ob->query("id");
                           tempname = user_ob->name(1);

                           if (type=="skill"){
                           if (user_ob->query_skill(func,1))
                           switch (tilde) {
                           case ">":  
                                  if (user_ob->query_skill(func,1)>val1){
                                        log_file("static/check_log",sprintf("%s[%s] %s:%d | ",tempid,tempname,func,user_ob->query_skill(func)));
                                  if3();
                                        }
                                        break;
                           case "<":
                                  if (user_ob->query_skill(func)<val1) {
                                        log_file("static/check_log",sprintf("%s[%s] %s:%d | ",tempid,tempname,func,user_ob->query_skill(func)));
                                        if3();
                                        }
                                        break;
                           case "=":
                                  if (user_ob->query_skill(func)==val1){
                                        log_file("static/check_log",sprintf("%s[%s] %s:%d | ",tempid,tempname,func,user_ob->query_skill(func)));
                                        if3();
                                        }
                                        break;
                                case "<>":
                                  if ((user_ob->query_skill(func)>val1) && (user_ob->query_skill(func)<val2)) {
                                        log_file("static/check_log",sprintf("%s[%s] %s:%d | ",tempid,tempname,func,user_ob->query_skill(func)));
                                        if3();
                                        }
                                        break;
                                }//switch
                                }//if (type=="skill")
                                else{
                           if (user_ob->query(func))
                           switch (tilde) {
                           case ">":  
                                  if (user_ob->query(func)>val1){
                                        log_file("static/check_log",sprintf("%s[%s] %s:%d | ",tempid,tempname,func,user_ob->query(func)));
                                  if3();
                                        }
                                        break;
                           case "<":
                                  if (user_ob->query(func)<val1) {
                                        log_file("static/check_log",sprintf("%s[%s] %s:%d | ",tempid,tempname,func,user_ob->query(func)));
                                        if3();
                                        }
                                        break;
                           case "=":
                                  if (user_ob->query(func)==val1){
                                        log_file("static/check_log",sprintf("%s[%s] %s:%d | ",tempid,tempname,func,user_ob->query(func)));
                                        if3();
                                        }
                                        break;
                                case "<>":
                                  if ((user_ob->query(func)>val1) && (user_ob->query(func)<val2)) {
                                        log_file("static/check_log",sprintf("%s[%s] %s:%d | ",tempid,tempname,func,user_ob->query(func)));
                                        if3();
                                        }
                                        break;
                                }//switch
                                }//else
                           if (!online) destruct(user_ob);
                      }//if( sscanf(ppls[j][0], "%s.o",tempid)==1 )
                }//for(j=0; j<sizeof(ppls); j++) {
        }//for(i=0; i<sizeof(dir); i++) {
        
        write("\n\n�ܹ���"+ ppl_cnt + "λʹ���ߡ�\n");
        write( count3 + " ��ʹ���߷��ϼ��Ҫ��\n");
        log_file("static/check_log", sprintf("\n�˴μ����%s[%s]��%s����!\n",this_player()->query("name"),geteuid(this_player()),ctime(time())[0..15]));
        return 1;
}//main

int if3()
{
       log_file("static/check_log",sprintf("\n"));
       count3++;
       return 1;
}

int help(object me)
{
        write(@HELP
ָ���ʽ: searchuser <skill|setting> <����> <������> <��ֵ1> [��ֵ2]
���MUD����������δ��������У�����ָ�������������Ϣ����¼
�����/log/static/check_logĿ¼�¡�
����skill��ʾ�����ҵ��书��setting��ʾ�����ҵ���������
���ԡ�
�������У�
>    ���ڷ���
<    С�ڷ���
=    ���ڷ���
<>   ���Σ���ʾ����ֵ1����ֵ2֮��

HELP );
        return 1;
}
