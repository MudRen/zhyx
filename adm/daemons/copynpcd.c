//���ڸ�����ҵ�ĳЩ���ݸ�һ��NPC��
//Ŀǰֻ�����ڷ���job

#include <ansi.h>
//copy_skill()
void copy_skill(object src,object des,int skill_multi,int status_multi){
        int num , max_skl , i;
        float exper;
        mapping skl , hp_status , skl_p;
        string *sname,*sname_p;
                hp_status = src->query_entire_dbase();
                des->set("max_qi",    status_multi*hp_status["max_qi"]/100);
                des->set("eff_qi",    status_multi*hp_status["max_qi"]/100);
                des->set("qi",        status_multi*hp_status["max_qi"]/100);
                des->set("max_jing",  status_multi*hp_status["max_jing"]/100);
                des->set("eff_jing",  status_multi*hp_status["max_jing"]/100);
                des->set("jing",      status_multi*hp_status["max_jing"]/100);
                des->set("max_neili", status_multi*hp_status["max_neili"]/100);
                des->set("neili",     status_multi*hp_status["max_neili"]/100);
                des->set("jiali",     50);
                des->set("combat_exp",status_multi*hp_status["combat_exp"]/100+5000);
                exper = to_float(des->query("combat_exp"));
                max_skl = ceil( pow( exper*10.0, 0.333333) );
                skl = des->query_skills();
                
                skl_p = src->query_skills();
                if (max_skl<80) max_skl = 80;

                if(!sizeof(skl_p)){
                        sname  = sort_array( keys(skl), (: strcmp :) );
                        for(i=0; i<sizeof(skl); i++){
                                des->set_skill(sname[i],max_skl);
                        }
                }else{
                        sname_p  = sort_array( keys(skl_p), (: strcmp :) );

                        for(i=0; i<sizeof(skl_p); i++){
                                if(skl_p[sname_p[i]] > max_skl) max_skl = skl_p[sname_p[i]];
                        }
//         max_skl -= 20;

                        if(max_skl < 80) max_skl = 80;

                        sname  = sort_array( keys(skl), (: strcmp :) );
                        for(i=0; i<sizeof(skl); i++){
                                des->set_skill(sname[i],skill_multi * max_skl/100);
                        }
                }
        return;
}
