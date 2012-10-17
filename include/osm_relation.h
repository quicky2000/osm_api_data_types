#ifndef _OSM_RELATION_H_
#define _OSM_RELATION_H_

#include "osm_core_element.h"
#include "osm_relation_member.h"
#include <vector>

namespace osm_diff_watcher
{
  class osm_relation: public osm_core_element
  {
    friend std::ostream & operator<<(std::ostream & p_stream,const osm_relation & p_relation);
  public:
    inline osm_relation(const t_osm_id  & p_id,
                        const std::string & p_timestamp,
                        const t_osm_version & p_version,
                        const t_osm_id & p_changeset,
                        const t_osm_id & p_user_id,
                        const std::string & p_user,
                        bool p_visible = true);

    inline void add_member(const osm_core_element::t_osm_type & p_type,
                           const osm_core_element::t_osm_id & p_object_ref,
                           const std::string & p_role);
    inline const std::vector<osm_relation_member*> & get_members(void)const;

    inline ~osm_relation(void);

    // Utilitie
    static inline const std::string & get_type_str(void);
  private:
    std::vector<osm_relation_member*> m_members;
    static const std::string m_type_str;
 };

  //------------------------------------------------------------------------------
  inline std::ostream & operator<<(std::ostream & p_stream,const osm_relation & p_relation)
    {
      p_stream << "relation id=" << p_relation.get_id() << " version=" << p_relation.get_version() << std::endl ;
      const std::vector<osm_relation_member*> & l_members = p_relation.get_members();
      for(std::vector<osm_relation_member*>::const_iterator l_iter = l_members.begin();
          l_iter != l_members.end();
          ++l_iter)
        {
          p_stream << **l_iter;
        }
 
      std::string l_tags_str;
      p_relation.tags_to_string(l_tags_str);
      p_stream << l_tags_str ;
      return p_stream;
    }

  //------------------------------------------------------------------------------
  const std::string & osm_relation::get_type_str(void)
    {
      return m_type_str;
    }

  //----------------------------------------------------------------------------
  osm_relation::osm_relation(const t_osm_id  & p_id,
                             const std::string & p_timestamp,
                             const t_osm_version & p_version,
                             const t_osm_id & p_changeset,
                             const t_osm_id & p_user_id,
                             const std::string & p_user,
                             bool p_visible):
    osm_core_element(p_id,true,p_timestamp,p_version,p_changeset,p_user_id,p_user)
    {
    }

  //----------------------------------------------------------------------------
    void osm_relation::add_member(const osm_core_element::t_osm_type & p_type,
                                  const osm_core_element::t_osm_id & p_object_ref,
                                  const std::string & p_role)
    {
      m_members.push_back(new osm_relation_member(p_type,p_object_ref,p_role));
    }

    //----------------------------------------------------------------------------
    osm_relation::~osm_relation(void)
    {
      for(std::vector<osm_relation_member*>::iterator l_iter = m_members.begin();
          l_iter != m_members.end();
          ++l_iter)
        {
          delete *l_iter;
        }
    }

    //----------------------------------------------------------------------------
    const std::vector<osm_relation_member*> & osm_relation::get_members(void)const
     {
       return m_members;
     }

}
#endif // _OSM_RELATION_H_
//EOF
