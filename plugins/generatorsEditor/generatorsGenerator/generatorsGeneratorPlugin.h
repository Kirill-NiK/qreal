#pragma once
#include "../../../qrgui/toolPluginInterface/toolPluginInterface.h"
#include <QtCore/QTranslator>
#include "generator.h"

namespace generators {
namespace generator {

class GeneratorsGeneratorPlugin : public QObject , public qReal::ToolPluginInterface
{
	Q_OBJECT
	Q_INTERFACES(qReal::ToolPluginInterface)
	Q_PLUGIN_METADATA(IID "generators.generator.GeneratorsGeneratorPlugin")

public:
	GeneratorsGeneratorPlugin();
	virtual ~GeneratorsGeneratorPlugin();

	/// Initializes generator with ref to logical model.
	virtual void init(qReal::PluginConfigurator const &configurator);

	/// Returns list containing "generate" action, which runs a generator.
	virtual QList<qReal::ActionInfo> actions();

private slots:
	void generate();
private:
	/// Compiles and loads to QReal new editor plugin
	void loadNewEditor(
			QString const &directoryName  ///< Directory where editor was generated (containing .pro file of that constraint)
			, QPair<QString, QString> const &pluginsNames /// GeneratorPluginNames
			, QString const &commandFirst  ///< qmake command
			, QString const &commandSecond  ///< make command
			, QString const &extension  ///< Extension of the resulting binary file with editor plugin (.dll/.so)
			, QString const &prefix  ///< Optional OS-dependent prefix for resulting binary file (lib for linux, for example)
			);

	void deleteGeneratedFiles(QString const &directoryName, QString const &fileBaseName);//qwerty_deleteFiles

	Generator mGenerator;

	/// Interface of MainWindow, used, for example, to reinit models when finished parsing
	qReal::gui::MainWindowInterpretersInterface *mMainWindowInterface;  // Does not have ownership

	/// Logical model, from which generator takes all information.
	qReal::LogicalModelAssistInterface const *mLogicalModel;

	/// Thanslator object for this plugin, provides localisation
	QTranslator mAppTranslator;

};

}
}