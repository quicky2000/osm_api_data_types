#ifndef _OSM_NODE_H_
#define _OSM_NODE_H_

#include "osm_core_element.h"
#include <iostream>

namespace osm_api_data_types
{
  class osm_node: public osm_core_element
  {
    friend std::ostream & operator<<(std::ostream & p_stream,const osm_node & p_node);
  public:
    // Constructor
    inline osm_node(const t_osm_id  & p_id,
		    const float & p_lat,
		    const float & p_lon,
		    const std::string & p_timestamp,
		    const t_osm_version & p_version,
		    const t_osm_id & p_changeset,
		    const t_osm_id & p_user_id,
		    const std::string & p_user,
		    bool p_visible = true);

    // Attributes accessors
    inline const float & get_lat(void)const;
    inline const float & get_lon(void)const;

    // Utilitie
    inline const osm_core_element::t_osm_type get_core_type(void)const;
    inline const std::string & get_core_type_str(void)const;
    static inline const std::string & get_type_str(void);
    static inline const osm_core_element::t_osm_type get_type(void);
  private:
    float m_lat;
    float m_lon;
    static const std::string m_type_str;
  };

  //------------------------------------------------------------------------------
  inline std::ostream & operator<<(std::ostream & p_stream,const osm_node & p_node)
    {
      p_stream << "node " << *((osm_core_element*)&p_node) << std::endl ;
      if(p_node.is_visible())
        {
          p_stream << "  lat=" << p_node.m_lat << " lon=" << p_node.m_lon << std::endl ;
        }
      std::string l_tags_str;
      p_node.tags_to_string(l_tags_str);
      p_stream << l_tags_str ;
      return p_stream;
    }

  //------------------------------------------------------------------------------
  osm_node::osm_node(const t_osm_id  & p_id,
		     const float & p_lat,
		     const float & p_lon,
		     const std::string & p_timestamp,
		     const t_osm_version & p_version,
		     const t_osm_id & p_changeset,
		     const t_osm_id & p_user_id,
		     const std::string & p_user,
		     bool p_visible):
    osm_core_element(p_id,true,p_timestamp,p_version,p_changeset,p_user_id,p_user),
    m_lat(p_lat),
    m_lon(p_lon)
      {
      }

    //------------------------------------------------------------------------------
    const std::string & osm_node::get_type_str(void)
      {
        return m_type_str;
      }

    //------------------------------------------------------------------------------
    const std::string & osm_node::get_core_type_str(void)const
      {
        return m_type_str;
      }

    //------------------------------------------------------------------------------
    const float & osm_node::get_lat(void)const
      {
	return m_lat;
      }

    //------------------------------------------------------------------------------
    const float & osm_node::get_lon(void)const
      {
	return m_lon;
      }
    //------------------------------------------------------------------------------
    const osm_core_element::t_osm_type osm_node::get_type(void)
      {
        return osm_core_element::NODE;
      }

    //------------------------------------------------------------------------------
    const osm_core_element::t_osm_type osm_node::get_core_type(void)const
      {
        return osm_core_element::NODE;
      }
}
#endif // _OSM_NODE_H_
