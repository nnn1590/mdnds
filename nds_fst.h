#ifndef _MD_NDS_FST_H
#define _MD_NDS_FST_H

#include <vector>
#include <map>
#include <cstdint>

#include "nds_header.h"
#include "util.h"

namespace nds
{
  struct FileEntry
  {
    FileEntry(std::string path, uint32_t begin, uint32_t end)
    {
      m_path = path;
      m_begin = begin;
      m_end = end;
    }

    inline std::string path()
    {
      return m_path.substr(2); // Gets rid of ./
    }

    inline uint32_t begin()
    {
      return m_begin;
    }

    inline uint32_t end()
    {
      return m_end;
    }

    inline uint32_t size()
    {
      return m_end - m_begin;
    }
  private:
    std::string m_path;
    uint32_t m_begin;
    uint32_t m_end;
  };

  struct TableEntry
  {
    TableEntry() : m_offset(0), m_first_id(0), m_parent_id(0) {};

    TableEntry(uint32_t offset, uint16_t first, uint16_t parent)
          : m_offset(offset), m_first_id(first), m_parent_id(parent) {};

    TableEntry(std::vector<uint8_t>& data, uint32_t offset = 0)
    {
      m_offset = util::read<uint32_t>(data, offset);
      m_first_id = util::read<uint16_t>(data, offset + 4);
      m_parent_id = util::read<uint16_t>(data, offset + 6);
    }

    inline uint32_t offset()
    {
      return m_offset;
    }

    inline uint16_t first_id()
    {
      return m_first_id;
    }

    inline uint16_t parent()
    {
      return m_parent_id;
    }

  private:
    uint32_t m_offset;
    uint16_t m_first_id;
    uint16_t m_parent_id;
  };

  class FST
  {
  public:
    FST(std::string disc);

    inline std::vector<FileEntry> files()
    {
      return m_entries;
    }
  private:
    std::vector<uint8_t> m_fat;
    std::vector<uint8_t> m_fnt;
    std::vector<FileEntry> m_entries;
    std::vector<TableEntry> m_table_entries;
  };
}

#endif
