#include "JenkinsJob.h"

JenkinsJob::JenkinsJob(QObject *parent)
  : QObject(parent)
  , m_name()
  , m_url()
  , m_color()
{
}

JenkinsJob::~JenkinsJob()
{
}

QString JenkinsJob::name() const
{
  return m_name;
}

void JenkinsJob::name(const QString &name)
{
  m_name = name;
}

QString JenkinsJob::url() const
{
  return m_url;
}

void JenkinsJob::url(const QString &url)
{
  m_url = url;
}

QString JenkinsJob::color() const
{
  return m_color;
}

void JenkinsJob::color(const QString &color)
{
  m_color = color;
}
