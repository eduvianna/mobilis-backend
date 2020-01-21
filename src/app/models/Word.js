import Sequelize, { Model } from 'sequelize';

class Word extends Model {
  static init(sequelize) {
    super.init(
      {
        sensor_id: Sequelize.STRING,
        word: Sequelize.INTEGER,
      },
      {
        sequelize,
        tableName: 'word',
      }
    );

    return this;
  }

  static associate(model) {
    this.hasMany(model.Sensor, { foreignKey: 'sensor_id', as: 'sensor' });
  }
}

export default Word;
